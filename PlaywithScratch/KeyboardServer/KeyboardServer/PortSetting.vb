Imports System.IO.Ports
Imports System.Threading

Public Class PortSetting
    Implements IDisposable

    Public Event OnStart(success As Boolean)
    Public Event OnStop()
    Public Event OnReceive([byte] As Byte)

    Private serialPort As SerialPort

    Private readThread As Thread
    Private [continue] As Boolean

    Public Property PortName As String
        Set(value As String)
            If serialPort.IsOpen Then StopListen()
            If value <> String.Empty Then serialPort.PortName = value
        End Set
        Get
            Return serialPort.PortName
        End Get
    End Property

    Public ReadOnly Property IsPortOpen As Boolean
        Get
            Return serialPort.IsOpen
        End Get
    End Property

    Public Sub New()
        serialPort = New SerialPort

        serialPort.BaudRate = 9600
        serialPort.Parity = Parity.None
        serialPort.DataBits = 8
        serialPort.StopBits = StopBits.One
        serialPort.Handshake = Handshake.None

        'serialPort.ReadTimeout = 500
        'serialPort.WriteTimeout = 500
    End Sub

    Public Sub StartListen()
        StopListen()

        Try
            serialPort.Open()

            readThread = New Thread(New ThreadStart(AddressOf Listen))

            [continue] = True
            readThread.Start()
        Catch ex As Exception
            RaiseEvent OnStart(False)
        End Try

        RaiseEvent OnStart(True)
    End Sub

    Public Sub StopListen()
        If serialPort.IsOpen Then
            [continue] = False
            readThread.Join()

            serialPort.Close()

            RaiseEvent OnStop()
        End If
    End Sub

    Private Sub Listen()
        While [continue]
            Try
                If serialPort.BytesToRead > 0 Then
                    RaiseEvent OnReceive(serialPort.ReadByte)
                End If
            Catch ex As Exception
                ' Do nothing
            End Try
        End While
    End Sub

    Public Sub Dispose() Implements IDisposable.Dispose
        [continue] = False
        If readThread IsNot Nothing AndAlso readThread.IsAlive Then readThread.Join()

        If serialPort.IsOpen Then serialPort.Close()
    End Sub

    Public Shared Function GetAllPorts() As String()
        Return SerialPort.GetPortNames()
    End Function
End Class
