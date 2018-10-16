Public Class MainForm

    Private cancelClosing As Boolean

    Private keySetting As KeySetting
    Private WithEvents portSetting As PortSetting

    Private Const CHANNEL_CHECKBOX_PREFIX = "chkCH"
    Private Const CHANNEL_COMBOBOX_PREFIX = "cboCH"

    Private Const BALLOON_TIMEOUT = 3000
    Private Const APPLICATION_TITLE = "Seeed Keyboard Server"

    Private Declare Sub keybd_event Lib "user32" _
        (ByVal bVk As Byte,
         ByVal bScan As Byte,
         ByVal dwFlags As Long,
         ByVal dwExtraInfo As Long)

    Public Sub New()
        InitializeComponent()

        cancelClosing = True

        keySetting = New KeySetting
        portSetting = New PortSetting

        AddHandler btnClose.Click, AddressOf Hide
        AddHandler icoNotify.MouseDoubleClick, AddressOf Show

        AddHandler mnStart.Click, AddressOf portSetting.StartListen
        AddHandler mnStop.Click, AddressOf portSetting.StopListen
    End Sub

    Private Sub LoadKeysSetting()
        For Each control As Control In tabKeySetting.Controls
            If TypeOf control Is CheckBox And control.Name.StartsWith(CHANNEL_CHECKBOX_PREFIX) Then
                Dim checkBox = CType(control, CheckBox)
                AddHandler checkBox.CheckedChanged, AddressOf ChannelOpenedChanged

                checkBox.Checked = keySetting.GetSetting(control.Name.Substring(CHANNEL_CHECKBOX_PREFIX.Length)).Opened
            End If

            If TypeOf control Is ComboBox And control.Name.StartsWith(CHANNEL_COMBOBOX_PREFIX) Then
                Dim comboBox = CType(control, ComboBox)
                AddHandler comboBox.SelectedIndexChanged, AddressOf ChannelBindingKeyChanged

                Dim bindingKey = keySetting.GetSetting(control.Name.Substring(CHANNEL_COMBOBOX_PREFIX.Length)).BindingKey
                comboBox.Items.AddRange(KeySetting.GetAllKeys)

                Dim bindingKeyIndex = comboBox.Items.IndexOf(bindingKey)
                comboBox.SelectedIndex = IIf(bindingKeyIndex = -1, 0, bindingKeyIndex)
            End If
        Next
    End Sub

    Private Sub ChannelOpenedChanged(sender As Object, e As EventArgs)
        Dim checkBox = CType(sender, CheckBox)
        Dim channel = CInt(checkBox.Name.Substring(CHANNEL_CHECKBOX_PREFIX.Length))

        keySetting.GetSetting(channel).Opened = checkBox.Checked
    End Sub

    Private Sub ChannelBindingKeyChanged(sender As Object, e As EventArgs)
        Dim comboBox = CType(sender, ComboBox)
        Dim channel = CInt(comboBox.Name.Substring(CHANNEL_COMBOBOX_PREFIX.Length))

        keySetting.GetSetting(channel).BindingKey = comboBox.Text
    End Sub

    Private Sub MainForm_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        RefreshPorts(Nothing, Nothing)
        LoadKeysSetting()
    End Sub

    Private Sub MainForm_Closing(sender As Object, e As EventArgs) Handles MyBase.FormClosing
        CType(e, FormClosingEventArgs).Cancel = cancelClosing
        If cancelClosing Then Hide()
    End Sub

    Private Sub StopServer(sender As Object, e As EventArgs) Handles mnQuit.Click
        keySetting.Dispose()
        portSetting.Dispose()

        cancelClosing = False
        Application.Exit()
    End Sub

    Private Sub SelectedPortChanged(sender As Object, e As EventArgs) Handles cboPorts.TextChanged
        portSetting.PortName = cboPorts.Text
    End Sub

    Private Sub RefreshPorts(sender As Object, e As EventArgs) Handles btnRefresh.Click
        cboPorts.Items.Clear()
        cboPorts.Items.AddRange(PortSetting.GetAllPorts)

        If portSetting.PortName IsNot Nothing AndAlso portSetting.PortName <> String.Empty Then
            cboPorts.Text = portSetting.PortName
        Else
            If cboPorts.Items.Count > 0 Then cboPorts.SelectedIndex = 0
        End If
    End Sub

    Private Sub OnPortStart(success As Boolean) Handles portSetting.OnStart
        If success Then
            mnStart.Checked = True
            mnStop.Checked = False

            icoNotify.ShowBalloonTip(BALLOON_TIMEOUT, APPLICATION_TITLE, "Port open success", ToolTipIcon.Info)
        Else
            icoNotify.ShowBalloonTip(BALLOON_TIMEOUT, APPLICATION_TITLE, "Port open failed", ToolTipIcon.Error)
        End If
    End Sub

    Private Sub OnPortStop() Handles portSetting.OnStop
        mnStart.Checked = False
        mnStop.Checked = True

        icoNotify.ShowBalloonTip(BALLOON_TIMEOUT, APPLICATION_TITLE, "Port closed", ToolTipIcon.Info)
    End Sub

    Private Sub OnPortReceive([byte] As Byte) Handles portSetting.OnReceive
        Dim checkBox = CType(tabKeySetting.Controls.Find(CHANNEL_CHECKBOX_PREFIX + CStr([byte] And &H7F), False).First, CheckBox)
        Dim comboBox = CType(tabKeySetting.Controls.Find(CHANNEL_COMBOBOX_PREFIX + CStr([byte] And &H7F), False).First, ComboBox)

        Dim bVk As Byte
        Dim enable As Boolean

        Invoke(Sub()
                   bVk = KeySetting.GetKey(comboBox.Text)
                   enable = checkBox.Checked
               End Sub)

        If enable Then
            keybd_event(bVk, 0, IIf([byte] And &H80, 2, 0), 0)
        End If
    End Sub
End Class
