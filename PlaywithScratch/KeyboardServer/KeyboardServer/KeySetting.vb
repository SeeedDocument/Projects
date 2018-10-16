Imports System.IO

Public Class KeySetting
    Implements IDisposable

    Private items As IDictionary(Of Integer, Item)

    Private Const STR_LENGTH = 32
    Private Const FILE_PATH = "./settings.ini"

    Private Const CHANNEL_COUNT = 12
    Private Const CHANNEL_PREFIX = "CH"

    Private Const OPENED_KEY = "Opened"
    Private Const BINDING_KEY_KEY = "BindingKey"
    Private Const DEFAULT_OPENED = "False"
    Private Const DEFAULT_BINDING_KEY = "None"

    Private Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" _
        (ByVal lpApplicationName As String,
         ByVal lpKeyName As String,
         ByVal lpDefault As String,
         ByVal lpReturnedString As String,
         ByVal nSize As Integer,
         ByVal lpFileName As String) As Integer

    Private Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" _
        (ByVal lpApplicationName As String,
         ByVal lpKeyName As String,
         ByVal lpString As String,
         ByVal lpFileName As String) As Integer

    Public Sub New()
        items = New Dictionary(Of Integer, Item)

        If File.Exists(FILE_PATH) Then
            LoadIniSettings()
        Else
            LoadDefaultSettings()

            Dim fs = File.Create(FILE_PATH)
            fs.Close()
        End If
    End Sub

    Public Function GetSetting(channel As Integer) As Item
        If Not items.ContainsKey(channel) Then Return Nothing

        Return items.Item(channel)
    End Function

    Public Sub Dispose() Implements IDisposable.Dispose
        For Each item In items
            Dim section = String.Concat(CHANNEL_PREFIX, item.Key)

            WritePrivateProfileString(section, OPENED_KEY, item.Value.Opened, FILE_PATH)
            WritePrivateProfileString(section, BINDING_KEY_KEY, item.Value.BindingKey, FILE_PATH)
        Next
    End Sub

    Private Sub LoadIniSettings()
        For i = 0 To CHANNEL_COUNT - 1
            Dim section = String.Concat(CHANNEL_PREFIX, i)

            Dim strOpened = LSet(String.Empty, STR_LENGTH)
            GetPrivateProfileString(section, OPENED_KEY, DEFAULT_OPENED, strOpened, STR_LENGTH, FILE_PATH)

            Dim bindingKey = LSet(String.Empty, STR_LENGTH)
            GetPrivateProfileString(section, BINDING_KEY_KEY, DEFAULT_BINDING_KEY, bindingKey, STR_LENGTH, FILE_PATH)

            Dim opened As Boolean = IIf(Boolean.TryParse(strOpened, opened), opened, False)
            items.Add(i, New Item(opened, bindingKey.Substring(0, bindingKey.IndexOf(vbNullChar))))
        Next
    End Sub

    Private Sub LoadDefaultSettings()
        For i = 0 To CHANNEL_COUNT - 1
            items.Add(i, New Item(DEFAULT_OPENED, DEFAULT_BINDING_KEY))
        Next
    End Sub

    Public Shared Function GetAllKeys() As String()
        Return [Enum].GetNames(GetType(Keys))
    End Function

    Public Shared Function GetKey(keyName As String) As Byte
        Return [Enum].Parse(GetType(Keys), keyName)
    End Function

    Public Class Item
        Private _opened As Boolean
        Private _bindingKey As String

        Public Property Opened As Boolean
            Set(value As Boolean)
                _opened = value
            End Set
            Get
                Return _opened
            End Get
        End Property

        Public Property BindingKey As String
            Set(value As String)
                _bindingKey = value
            End Set
            Get
                Return _bindingKey
            End Get
        End Property

        Public Sub New(open As Boolean, bindingKey As String)
            _opened = open
            _bindingKey = bindingKey
        End Sub
    End Class
End Class
