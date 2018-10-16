<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class MainForm
    Inherits System.Windows.Forms.Form

    'Form 重写 Dispose，以清理组件列表。
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改它。  
    '不要使用代码编辑器修改它。
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(MainForm))
        Me.btnClose = New System.Windows.Forms.Button()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.cboPorts = New System.Windows.Forms.ComboBox()
        Me.icoNotify = New System.Windows.Forms.NotifyIcon(Me.components)
        Me.mnuNotify = New System.Windows.Forms.ContextMenuStrip(Me.components)
        Me.mnStart = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnStop = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnQuit = New System.Windows.Forms.ToolStripMenuItem()
        Me.Panel1 = New System.Windows.Forms.Panel()
        Me.TabControl1 = New System.Windows.Forms.TabControl()
        Me.TabPage1 = New System.Windows.Forms.TabPage()
        Me.btnRefresh = New System.Windows.Forms.Button()
        Me.tabKeySetting = New System.Windows.Forms.TabPage()
        Me.chkCH11 = New System.Windows.Forms.CheckBox()
        Me.chkCH10 = New System.Windows.Forms.CheckBox()
        Me.chkCH9 = New System.Windows.Forms.CheckBox()
        Me.chkCH8 = New System.Windows.Forms.CheckBox()
        Me.chkCH7 = New System.Windows.Forms.CheckBox()
        Me.cboCH11 = New System.Windows.Forms.ComboBox()
        Me.cboCH10 = New System.Windows.Forms.ComboBox()
        Me.cboCH9 = New System.Windows.Forms.ComboBox()
        Me.cboCH8 = New System.Windows.Forms.ComboBox()
        Me.cboCH7 = New System.Windows.Forms.ComboBox()
        Me.cboCH6 = New System.Windows.Forms.ComboBox()
        Me.chkCH6 = New System.Windows.Forms.CheckBox()
        Me.chkCH5 = New System.Windows.Forms.CheckBox()
        Me.chkCH4 = New System.Windows.Forms.CheckBox()
        Me.chkCH3 = New System.Windows.Forms.CheckBox()
        Me.chkCH2 = New System.Windows.Forms.CheckBox()
        Me.cboCH5 = New System.Windows.Forms.ComboBox()
        Me.cboCH4 = New System.Windows.Forms.ComboBox()
        Me.cboCH3 = New System.Windows.Forms.ComboBox()
        Me.cboCH2 = New System.Windows.Forms.ComboBox()
        Me.cboCH1 = New System.Windows.Forms.ComboBox()
        Me.chkCH1 = New System.Windows.Forms.CheckBox()
        Me.chkCH0 = New System.Windows.Forms.CheckBox()
        Me.cboCH0 = New System.Windows.Forms.ComboBox()
        Me.mnuNotify.SuspendLayout()
        Me.Panel1.SuspendLayout()
        Me.TabControl1.SuspendLayout()
        Me.TabPage1.SuspendLayout()
        Me.tabKeySetting.SuspendLayout()
        Me.SuspendLayout()
        '
        'btnClose
        '
        Me.btnClose.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnClose.Location = New System.Drawing.Point(377, 15)
        Me.btnClose.Name = "btnClose"
        Me.btnClose.Size = New System.Drawing.Size(75, 23)
        Me.btnClose.TabIndex = 1
        Me.btnClose.Text = "Close"
        Me.btnClose.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(3, 18)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(59, 12)
        Me.Label1.TabIndex = 4
        Me.Label1.Text = "Port Name"
        '
        'cboPorts
        '
        Me.cboPorts.FormattingEnabled = True
        Me.cboPorts.Location = New System.Drawing.Point(63, 15)
        Me.cboPorts.Name = "cboPorts"
        Me.cboPorts.Size = New System.Drawing.Size(121, 20)
        Me.cboPorts.TabIndex = 5
        '
        'icoNotify
        '
        Me.icoNotify.ContextMenuStrip = Me.mnuNotify
        Me.icoNotify.Icon = CType(resources.GetObject("icoNotify.Icon"), System.Drawing.Icon)
        Me.icoNotify.Text = "Seeed Keyboard Server"
        Me.icoNotify.Visible = True
        '
        'mnuNotify
        '
        Me.mnuNotify.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnStart, Me.mnStop, Me.mnQuit})
        Me.mnuNotify.Name = "mnuNotify"
        Me.mnuNotify.Size = New System.Drawing.Size(153, 92)
        '
        'mnStart
        '
        Me.mnStart.Name = "mnStart"
        Me.mnStart.Size = New System.Drawing.Size(152, 22)
        Me.mnStart.Text = "Start"
        '
        'mnStop
        '
        Me.mnStop.Checked = True
        Me.mnStop.CheckState = System.Windows.Forms.CheckState.Checked
        Me.mnStop.Name = "mnStop"
        Me.mnStop.Size = New System.Drawing.Size(152, 22)
        Me.mnStop.Text = "Stop"
        '
        'mnQuit
        '
        Me.mnQuit.Name = "mnQuit"
        Me.mnQuit.Size = New System.Drawing.Size(152, 22)
        Me.mnQuit.Text = "Quit"
        '
        'Panel1
        '
        Me.Panel1.Controls.Add(Me.btnClose)
        Me.Panel1.Dock = System.Windows.Forms.DockStyle.Bottom
        Me.Panel1.Location = New System.Drawing.Point(0, 511)
        Me.Panel1.Name = "Panel1"
        Me.Panel1.Size = New System.Drawing.Size(464, 50)
        Me.Panel1.TabIndex = 6
        '
        'TabControl1
        '
        Me.TabControl1.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.TabControl1.Controls.Add(Me.TabPage1)
        Me.TabControl1.Controls.Add(Me.tabKeySetting)
        Me.TabControl1.Location = New System.Drawing.Point(12, 12)
        Me.TabControl1.Name = "TabControl1"
        Me.TabControl1.SelectedIndex = 0
        Me.TabControl1.Size = New System.Drawing.Size(440, 499)
        Me.TabControl1.TabIndex = 2
        '
        'TabPage1
        '
        Me.TabPage1.Controls.Add(Me.btnRefresh)
        Me.TabPage1.Controls.Add(Me.cboPorts)
        Me.TabPage1.Controls.Add(Me.Label1)
        Me.TabPage1.Location = New System.Drawing.Point(4, 22)
        Me.TabPage1.Name = "TabPage1"
        Me.TabPage1.Padding = New System.Windows.Forms.Padding(3)
        Me.TabPage1.Size = New System.Drawing.Size(432, 473)
        Me.TabPage1.TabIndex = 0
        Me.TabPage1.Text = "Ports"
        Me.TabPage1.UseVisualStyleBackColor = True
        '
        'btnRefresh
        '
        Me.btnRefresh.Location = New System.Drawing.Point(190, 13)
        Me.btnRefresh.Name = "btnRefresh"
        Me.btnRefresh.Size = New System.Drawing.Size(75, 23)
        Me.btnRefresh.TabIndex = 6
        Me.btnRefresh.Text = "Refresh"
        Me.btnRefresh.UseVisualStyleBackColor = True
        '
        'tabKeySetting
        '
        Me.tabKeySetting.Controls.Add(Me.chkCH11)
        Me.tabKeySetting.Controls.Add(Me.chkCH10)
        Me.tabKeySetting.Controls.Add(Me.chkCH9)
        Me.tabKeySetting.Controls.Add(Me.chkCH8)
        Me.tabKeySetting.Controls.Add(Me.chkCH7)
        Me.tabKeySetting.Controls.Add(Me.cboCH11)
        Me.tabKeySetting.Controls.Add(Me.cboCH10)
        Me.tabKeySetting.Controls.Add(Me.cboCH9)
        Me.tabKeySetting.Controls.Add(Me.cboCH8)
        Me.tabKeySetting.Controls.Add(Me.cboCH7)
        Me.tabKeySetting.Controls.Add(Me.cboCH6)
        Me.tabKeySetting.Controls.Add(Me.chkCH6)
        Me.tabKeySetting.Controls.Add(Me.chkCH5)
        Me.tabKeySetting.Controls.Add(Me.chkCH4)
        Me.tabKeySetting.Controls.Add(Me.chkCH3)
        Me.tabKeySetting.Controls.Add(Me.chkCH2)
        Me.tabKeySetting.Controls.Add(Me.cboCH5)
        Me.tabKeySetting.Controls.Add(Me.cboCH4)
        Me.tabKeySetting.Controls.Add(Me.cboCH3)
        Me.tabKeySetting.Controls.Add(Me.cboCH2)
        Me.tabKeySetting.Controls.Add(Me.cboCH1)
        Me.tabKeySetting.Controls.Add(Me.chkCH1)
        Me.tabKeySetting.Controls.Add(Me.chkCH0)
        Me.tabKeySetting.Controls.Add(Me.cboCH0)
        Me.tabKeySetting.Location = New System.Drawing.Point(4, 22)
        Me.tabKeySetting.Name = "tabKeySetting"
        Me.tabKeySetting.Padding = New System.Windows.Forms.Padding(3)
        Me.tabKeySetting.Size = New System.Drawing.Size(432, 473)
        Me.tabKeySetting.TabIndex = 1
        Me.tabKeySetting.Text = "Keys"
        Me.tabKeySetting.UseVisualStyleBackColor = True
        '
        'chkCH11
        '
        Me.chkCH11.AutoSize = True
        Me.chkCH11.Location = New System.Drawing.Point(199, 195)
        Me.chkCH11.Name = "chkCH11"
        Me.chkCH11.Size = New System.Drawing.Size(48, 16)
        Me.chkCH11.TabIndex = 24
        Me.chkCH11.Text = "CH11"
        Me.chkCH11.UseVisualStyleBackColor = True
        '
        'chkCH10
        '
        Me.chkCH10.AutoSize = True
        Me.chkCH10.Location = New System.Drawing.Point(199, 160)
        Me.chkCH10.Name = "chkCH10"
        Me.chkCH10.Size = New System.Drawing.Size(48, 16)
        Me.chkCH10.TabIndex = 23
        Me.chkCH10.Text = "CH10"
        Me.chkCH10.UseVisualStyleBackColor = True
        '
        'chkCH9
        '
        Me.chkCH9.AutoSize = True
        Me.chkCH9.Location = New System.Drawing.Point(199, 124)
        Me.chkCH9.Name = "chkCH9"
        Me.chkCH9.Size = New System.Drawing.Size(42, 16)
        Me.chkCH9.TabIndex = 22
        Me.chkCH9.Text = "CH9"
        Me.chkCH9.UseVisualStyleBackColor = True
        '
        'chkCH8
        '
        Me.chkCH8.AutoSize = True
        Me.chkCH8.Location = New System.Drawing.Point(199, 88)
        Me.chkCH8.Name = "chkCH8"
        Me.chkCH8.Size = New System.Drawing.Size(42, 16)
        Me.chkCH8.TabIndex = 21
        Me.chkCH8.Text = "CH8"
        Me.chkCH8.UseVisualStyleBackColor = True
        '
        'chkCH7
        '
        Me.chkCH7.AutoSize = True
        Me.chkCH7.Location = New System.Drawing.Point(199, 53)
        Me.chkCH7.Name = "chkCH7"
        Me.chkCH7.Size = New System.Drawing.Size(42, 16)
        Me.chkCH7.TabIndex = 20
        Me.chkCH7.Text = "CH7"
        Me.chkCH7.UseVisualStyleBackColor = True
        '
        'cboCH11
        '
        Me.cboCH11.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH11.FormattingEnabled = True
        Me.cboCH11.Location = New System.Drawing.Point(247, 193)
        Me.cboCH11.Name = "cboCH11"
        Me.cboCH11.Size = New System.Drawing.Size(121, 20)
        Me.cboCH11.TabIndex = 19
        '
        'cboCH10
        '
        Me.cboCH10.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH10.FormattingEnabled = True
        Me.cboCH10.Location = New System.Drawing.Point(247, 158)
        Me.cboCH10.Name = "cboCH10"
        Me.cboCH10.Size = New System.Drawing.Size(121, 20)
        Me.cboCH10.TabIndex = 18
        '
        'cboCH9
        '
        Me.cboCH9.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH9.FormattingEnabled = True
        Me.cboCH9.Location = New System.Drawing.Point(247, 122)
        Me.cboCH9.Name = "cboCH9"
        Me.cboCH9.Size = New System.Drawing.Size(121, 20)
        Me.cboCH9.TabIndex = 17
        '
        'cboCH8
        '
        Me.cboCH8.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH8.FormattingEnabled = True
        Me.cboCH8.Location = New System.Drawing.Point(247, 86)
        Me.cboCH8.Name = "cboCH8"
        Me.cboCH8.Size = New System.Drawing.Size(121, 20)
        Me.cboCH8.TabIndex = 16
        '
        'cboCH7
        '
        Me.cboCH7.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH7.FormattingEnabled = True
        Me.cboCH7.Location = New System.Drawing.Point(247, 51)
        Me.cboCH7.Name = "cboCH7"
        Me.cboCH7.Size = New System.Drawing.Size(121, 20)
        Me.cboCH7.TabIndex = 15
        '
        'cboCH6
        '
        Me.cboCH6.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH6.FormattingEnabled = True
        Me.cboCH6.Location = New System.Drawing.Point(247, 15)
        Me.cboCH6.Name = "cboCH6"
        Me.cboCH6.Size = New System.Drawing.Size(121, 20)
        Me.cboCH6.TabIndex = 14
        '
        'chkCH6
        '
        Me.chkCH6.AutoSize = True
        Me.chkCH6.Location = New System.Drawing.Point(199, 17)
        Me.chkCH6.Name = "chkCH6"
        Me.chkCH6.Size = New System.Drawing.Size(42, 16)
        Me.chkCH6.TabIndex = 13
        Me.chkCH6.Text = "CH6"
        Me.chkCH6.UseVisualStyleBackColor = True
        '
        'chkCH5
        '
        Me.chkCH5.AutoSize = True
        Me.chkCH5.Location = New System.Drawing.Point(15, 195)
        Me.chkCH5.Name = "chkCH5"
        Me.chkCH5.Size = New System.Drawing.Size(42, 16)
        Me.chkCH5.TabIndex = 12
        Me.chkCH5.Text = "CH5"
        Me.chkCH5.UseVisualStyleBackColor = True
        '
        'chkCH4
        '
        Me.chkCH4.AutoSize = True
        Me.chkCH4.Location = New System.Drawing.Point(15, 160)
        Me.chkCH4.Name = "chkCH4"
        Me.chkCH4.Size = New System.Drawing.Size(42, 16)
        Me.chkCH4.TabIndex = 11
        Me.chkCH4.Text = "CH4"
        Me.chkCH4.UseVisualStyleBackColor = True
        '
        'chkCH3
        '
        Me.chkCH3.AutoSize = True
        Me.chkCH3.Location = New System.Drawing.Point(15, 124)
        Me.chkCH3.Name = "chkCH3"
        Me.chkCH3.Size = New System.Drawing.Size(42, 16)
        Me.chkCH3.TabIndex = 10
        Me.chkCH3.Text = "CH3"
        Me.chkCH3.UseVisualStyleBackColor = True
        '
        'chkCH2
        '
        Me.chkCH2.AutoSize = True
        Me.chkCH2.Location = New System.Drawing.Point(15, 88)
        Me.chkCH2.Name = "chkCH2"
        Me.chkCH2.Size = New System.Drawing.Size(42, 16)
        Me.chkCH2.TabIndex = 9
        Me.chkCH2.Text = "CH2"
        Me.chkCH2.UseVisualStyleBackColor = True
        '
        'cboCH5
        '
        Me.cboCH5.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH5.FormattingEnabled = True
        Me.cboCH5.Location = New System.Drawing.Point(63, 193)
        Me.cboCH5.Name = "cboCH5"
        Me.cboCH5.Size = New System.Drawing.Size(121, 20)
        Me.cboCH5.TabIndex = 8
        '
        'cboCH4
        '
        Me.cboCH4.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH4.FormattingEnabled = True
        Me.cboCH4.Location = New System.Drawing.Point(63, 158)
        Me.cboCH4.Name = "cboCH4"
        Me.cboCH4.Size = New System.Drawing.Size(121, 20)
        Me.cboCH4.TabIndex = 7
        '
        'cboCH3
        '
        Me.cboCH3.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH3.FormattingEnabled = True
        Me.cboCH3.Location = New System.Drawing.Point(63, 122)
        Me.cboCH3.Name = "cboCH3"
        Me.cboCH3.Size = New System.Drawing.Size(121, 20)
        Me.cboCH3.TabIndex = 6
        '
        'cboCH2
        '
        Me.cboCH2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH2.FormattingEnabled = True
        Me.cboCH2.Location = New System.Drawing.Point(63, 86)
        Me.cboCH2.Name = "cboCH2"
        Me.cboCH2.Size = New System.Drawing.Size(121, 20)
        Me.cboCH2.TabIndex = 5
        '
        'cboCH1
        '
        Me.cboCH1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH1.FormattingEnabled = True
        Me.cboCH1.Location = New System.Drawing.Point(63, 51)
        Me.cboCH1.Name = "cboCH1"
        Me.cboCH1.Size = New System.Drawing.Size(121, 20)
        Me.cboCH1.TabIndex = 4
        '
        'chkCH1
        '
        Me.chkCH1.AutoSize = True
        Me.chkCH1.Location = New System.Drawing.Point(15, 53)
        Me.chkCH1.Name = "chkCH1"
        Me.chkCH1.Size = New System.Drawing.Size(42, 16)
        Me.chkCH1.TabIndex = 3
        Me.chkCH1.Text = "CH1"
        Me.chkCH1.UseVisualStyleBackColor = True
        '
        'chkCH0
        '
        Me.chkCH0.AutoSize = True
        Me.chkCH0.Location = New System.Drawing.Point(15, 17)
        Me.chkCH0.Name = "chkCH0"
        Me.chkCH0.Size = New System.Drawing.Size(42, 16)
        Me.chkCH0.TabIndex = 2
        Me.chkCH0.Text = "CH0"
        Me.chkCH0.UseVisualStyleBackColor = True
        '
        'cboCH0
        '
        Me.cboCH0.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboCH0.FormattingEnabled = True
        Me.cboCH0.Location = New System.Drawing.Point(63, 15)
        Me.cboCH0.Name = "cboCH0"
        Me.cboCH0.Size = New System.Drawing.Size(121, 20)
        Me.cboCH0.TabIndex = 0
        '
        'MainForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(464, 561)
        Me.Controls.Add(Me.TabControl1)
        Me.Controls.Add(Me.Panel1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "MainForm"
        Me.ShowInTaskbar = False
        Me.Text = "Settings"
        Me.TopMost = True
        Me.mnuNotify.ResumeLayout(False)
        Me.Panel1.ResumeLayout(False)
        Me.TabControl1.ResumeLayout(False)
        Me.TabPage1.ResumeLayout(False)
        Me.TabPage1.PerformLayout()
        Me.tabKeySetting.ResumeLayout(False)
        Me.tabKeySetting.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents btnClose As Button
    Friend WithEvents Label1 As Label
    Friend WithEvents cboPorts As ComboBox
    Friend WithEvents icoNotify As NotifyIcon
    Friend WithEvents Panel1 As Panel
    Friend WithEvents TabControl1 As TabControl
    Friend WithEvents TabPage1 As TabPage
    Friend WithEvents tabKeySetting As TabPage
    Friend WithEvents cboCH1 As ComboBox
    Friend WithEvents chkCH1 As CheckBox
    Friend WithEvents chkCH0 As CheckBox
    Friend WithEvents cboCH0 As ComboBox
    Friend WithEvents chkCH5 As CheckBox
    Friend WithEvents chkCH4 As CheckBox
    Friend WithEvents chkCH3 As CheckBox
    Friend WithEvents chkCH2 As CheckBox
    Friend WithEvents cboCH5 As ComboBox
    Friend WithEvents cboCH4 As ComboBox
    Friend WithEvents cboCH3 As ComboBox
    Friend WithEvents cboCH2 As ComboBox
    Friend WithEvents chkCH11 As CheckBox
    Friend WithEvents chkCH10 As CheckBox
    Friend WithEvents chkCH9 As CheckBox
    Friend WithEvents chkCH8 As CheckBox
    Friend WithEvents chkCH7 As CheckBox
    Friend WithEvents cboCH11 As ComboBox
    Friend WithEvents cboCH10 As ComboBox
    Friend WithEvents cboCH9 As ComboBox
    Friend WithEvents cboCH8 As ComboBox
    Friend WithEvents cboCH7 As ComboBox
    Friend WithEvents cboCH6 As ComboBox
    Friend WithEvents chkCH6 As CheckBox
    Friend WithEvents mnuNotify As ContextMenuStrip
    Friend WithEvents mnStart As ToolStripMenuItem
    Friend WithEvents mnStop As ToolStripMenuItem
    Friend WithEvents mnQuit As ToolStripMenuItem
    Friend WithEvents btnRefresh As Button
End Class
