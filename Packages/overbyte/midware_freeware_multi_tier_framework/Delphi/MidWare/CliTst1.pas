{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Sample client for the sample application server using
              F. Piette's Middleware (MidWare).
Creation:     March 3, 1998
Version:      2.02
EMail:        francois.piette@overbyte.be   francois.piette@rtfm.be
              http://www.overbyte.be        http://www.rtfm.be/fpiette
              francois.piette@pophost.eunet.be
Support:      Use the mailing list midware@elists.org
              Follow "support" link at http://www.overbyte.be for subscription.
Legal issues: Copyright (C) 1997-2001 by François PIETTE
              Rue de Grady 24, 4053 Embourg, Belgium. Fax: +32-4-365.74.56
              <francois.piette@overbyte.be> <francois.piette@pophost.eunet.be>

              This software is provided 'as-is', without any express or
              implied warranty. In no event will the author be held liable
              for any damages arising from the use of this software.

              Permission is granted to anyone to use this software and or any
              derived or altered versions for any purpose, excluding commercial
              applications. You can use this software for personal use only.
              You may distribute it freely untouched.
              The following restrictions applies:

              1. The origin of this software must not be misrepresented, you
                 must not claim that you wrote the original software.

              2. If you use this software in a product, an acknowledgment in
                 the product documentation and displayed on screen is required.
                 The text must be: "This product is based on MidWare. Freeware
                 source code is available at http://www.rtfm.be/fpiette."

              3. Altered source versions must be plainly marked as such, and
                 must not be misrepresented as being the original software.

              4. This notice may not be removed or altered from any source
                 distribution and must be added to the product documentation.

Updates:
Mar 24, 1998  V1.01 Added a missing TMWBuffer
Mar 25, 1998  V1.02 Displayed and numbered all records in the answer from server
Apr 24, 1998  V1.03 Adapted the sample program to support the new server object
              (SrvObj5, function GETFILE) to display BMP files in a separate
              window.
May 19, 1998  V1.04 Added edit boxes to change server host name and port.
              Added version display on startup.
Jun 07, 1998  V1.05 Implemented encryption in commands and replies.
Nov 07, 1998  V1.06 Corrected AppSrvClient1BeforeProcessReply to return
              updated CmdLen after decryption.
Nov 22, 1998  V2.00 Added socks support.
Mar 26, 1999  V2.01 Added code to support LZH compression. See LZH define.
Apr 16, 1998  V2.02 Fixed memory allocation bug related to LZH


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit CliTst1;
{$DEFINE LZH}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, IniFiles, WSocket, WinSock, RFormat, ApsCli,
{$IFDEF LZH}
  CipherLz;
{$ELSE}
  Cipher;
{$ENDIF}

const
  CliTstVersion = 202;

type
  TTestClientForm = class(TForm)
    Memo1: TMemo;
    Panel1: TPanel;
    SendButton: TButton;
    DisconnectButton: TButton;
    DataEdit: TEdit;
    FunctionEdit: TEdit;
    ClearButton: TButton;
    AppSrvClient1: TAppSrvClient;
    MWBuffer1: TMWBuffer;
    Label1: TLabel;
    Label2: TLabel;
    RepeatButton: TButton;
    GroupBox1: TGroupBox;
    Label3: TLabel;
    ServerEdit: TEdit;
    Label6: TLabel;
    PortEdit: TEdit;
    EncryptCheckBox: TCheckBox;
    GroupBox2: TGroupBox;
    Label4: TLabel;
    SocksServerEdit: TEdit;
    Label5: TLabel;
    SocksPortEdit: TEdit;
    Label7: TLabel;
    Label8: TLabel;
    SocksUsercodeEdit: TEdit;
    SocksPasswordEdit: TEdit;
    SocksAuthCheckBox: TCheckBox;
    procedure SendButtonClick(Sender: TObject);
    procedure DisconnectButtonClick(Sender: TObject);
    procedure ClearButtonClick(Sender: TObject);
    procedure AppSrvClient1RequestDone(Sender: TObject; Error: Integer);
    procedure AppSrvClient1SessionClosed(Sender: TObject; Error: Word);
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure AppSrvClient1BeforeProcessReply(Sender: TObject;
      var CmdBuf: PChar; var CmdLen: Integer);
    procedure AppSrvClient1BeforeSendRequest(Sender: TObject);
    procedure AppSrvClient1AfterSendRequest(Sender: TObject);
    procedure RepeatButtonClick(Sender: TObject);
    procedure AppSrvClient1SocksConnected(Sender: TObject; Error: Word);
    procedure AppSrvClient1SessionConnected(Sender: TObject; Error: Word);
    procedure AppSrvClient1BannerRcvd(Sender: TObject; CmdBuf: PChar;
      CmdLen: Integer; var BannerOk: Boolean);
    procedure AppSrvClient1SocksError(Sender: TObject; Error: Integer;
      Msg: String);
    procedure AppSrvClient1SocksAuthState(Sender: TObject;
      AuthState: TSocksAuthState);
    procedure AppSrvClient1AfterProcessReply(Sender: TObject;
      var CmdBuf: PChar; var CmdLen: Integer);
  private
    FIniFileName : String;
    FInitialized : Boolean;
    FPort        : String;
    FServer      : String;
    FRepeatFlag  : Boolean;
    FRepeatCount : Integer;
    FEncryptFlag : Boolean;
    procedure DisplayBmpFile;
    procedure ImageFormClose(Sender: TObject; var Action: TCloseAction);
  public
    { Déclarations publiques }
  end;

var
  TestClientForm: TTestClientForm;

implementation

{$R *.DFM}

const
    SectionData      = 'Data';
    KeyPort          = 'Port';
    KeyServer        = 'Server';
    SectionWindow    = 'Window';
    KeyTop           = 'Top';
    KeyLeft          = 'Left';
    KeyWidth         = 'Width';
    KeyHeight        = 'Height';
    KeyData          = 'Data';
    KeyFunction      = 'Function';
    KeyEncrypt       = 'Encrypt';
    KeySocksServer   = 'SocksServer';
    KeySocksPort     = 'SocksPort';
    KeySocksUsercode = 'SocksUsercode';
    KeySocksPassword = 'SocksPassword';
    KeySocksAuth     = 'SocksAuthentication';


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.FormCreate(Sender: TObject);
begin
    FIniFileName := LowerCase(ExtractFileName(Application.ExeName));
    FIniFileName := Copy(FIniFileName, 1, Length(FIniFileName) - 3) + 'ini';
    Memo1.Clear;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.FormShow(Sender: TObject);
var
    IniFile : TIniFile;
    Data    : TWSAData;
begin
    if not FInitialized then begin
        FInitialized := TRUE;
        IniFile      := TIniFile.Create(FIniFileName);
        Width   := IniFile.ReadInteger(SectionWindow, KeyWidth,  Width);
        Height  := IniFile.ReadInteger(SectionWindow, KeyHeight, Height);
        Top     := IniFile.ReadInteger(SectionWindow, KeyTop,    (Screen.Height - Height) div 2);
        Left    := IniFile.ReadInteger(SectionWindow, KeyLeft,   (Screen.Width  - Width) div 2);
        FPort   := IniFile.ReadString(SectionData,    KeyPort,   '2106');
        FServer := IniFile.ReadString(SectionData,    KeyServer, 'localhost');

        DataEdit.Text     := IniFile.ReadString(SectionData,
                                                KeyData, 'Piette');
        FunctionEdit.Text := IniFile.ReadString(SectionData,
                                                KeyFunction, 'GETCLIENT');
        EncryptCheckBox.Checked := (IniFile.ReadInteger(SectionData,
                                                KeyEncrypt, 0) <> 0);
        SocksServerEdit.Text    := IniFile.ReadString(SectionData,
                                                      KeySocksServer, '');
        SocksPortEdit.Text      := IniFile.ReadString(SectionData,
                                                      KeySocksPort, '1080');
        SocksUsercodeEdit.Text  := IniFile.ReadString(SectionData,
                                                      KeySocksUsercode, '');
        SocksPasswordEdit.Text  := IniFile.ReadString(SectionData,
                                                      KeySocksPassword, '');
        SocksAuthCheckBox.Checked := Boolean(IniFile.ReadInteger(SectionData,
                                                      KeySocksAuth, 0));
        IniFile.Free;

        PortEdit.Text   := FPort;
        ServerEdit.Text := FServer;

        { Display all pertinent info versions }
        Memo1.Lines.Add(Format('Program version %d.%2.2d' ,
                        [CliTstVersion div 100, CliTstVersion mod 100]));
        Memo1.Lines.Add(Format('AppSrvClient client version %d.%2.2d' ,
                        [AppSrvClientVersion div 100, AppSrvClientVersion mod 100]));
        Memo1.Lines.Add(Format('MWBuffer version %d.%2.2d' ,
                        [MWBufferVersion div 100, MWBufferVersion mod 100]));
        Memo1.Lines.Add(Format('TWSocket version %d.%2.2d' ,
                        [WSocketVersion div 100, WSocketVersion mod 100]));
        Data := WinsockInfo;
        Memo1.Lines.Add('Winsock verion ' +
                              IntToStr(LOBYTE(Data.wVersion)) + '.' +
                              IntToStr(HIBYTE(Data.wVersion)));
        Memo1.Lines.Add(StrPas(Data.szDescription));
        Memo1.Lines.Add(StrPas(Data.szSystemStatus));
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.FormClose(Sender: TObject;
  var Action: TCloseAction);
var
    IniFile : TIniFile;
begin
    IniFile := TIniFile.Create(FIniFileName);
    IniFile.WriteInteger(SectionWindow, KeyTop,      Top);
    IniFile.WriteInteger(SectionWindow, KeyLeft,     Left);
    IniFile.WriteInteger(SectionWindow, KeyWidth,    Width);
    IniFile.WriteInteger(SectionWindow, KeyHeight,   Height);
    IniFile.WriteInteger(SectionData,   KeyEncrypt,  Ord(EncryptCheckBox.Checked));
    IniFile.WriteString(SectionData,    KeyPort,     PortEdit.Text);
    IniFile.WriteString(SectionData,    KeyServer,   ServerEdit.Text);
    IniFile.WriteString(SectionData,    KeyData,     DataEdit.Text);
    IniFile.WriteString(SectionData,    KeyFunction, FunctionEdit.Text);
    IniFile.WriteString(SectionData,    KeySocksServer,     SocksServerEdit.Text);
    IniFile.WriteString(SectionData,    KeySocksPort,       SocksPortEdit.Text);
    IniFile.WriteString(SectionData,    KeySocksUsercode,   SocksUsercodeEdit.Text);
    IniFile.WriteString(SectionData,    KeySocksPassword,   SocksPasswordEdit.Text);
    IniFile.WriteInteger(SectionData, KeySocksAuth, Ord(SocksAuthCheckBox.Checked));
    IniFile.Free;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.DisconnectButtonClick(Sender: TObject);
begin
    AppSrvClient1.Close;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.ClearButtonClick(Sender: TObject);
begin
    if FRepeatFlag then
        FRepeatFlag := FALSE
    else
        Memo1.Clear;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.SendButtonClick(Sender: TObject);
const
    AuthMethod : array [Boolean] of TSocksAuthentication =
        (socksNoAuthentication, socksAuthenticateUsercode);
var
    Data     : TFileStream;
    FileName : String;
begin
    DisconnectButton.Enabled   := TRUE;
    FRepeatFlag                := (Sender = RepeatButton);
    if FRepeatFlag then begin
        Inc(FRepeatCount);
        Memo1.Lines.Add('Repeat ' + IntToStr(FRepeatCount));
    end;
    AppSrvClient1.Request.Rewrite;
    AppSrvClient1.FunctionCode := Trim(FunctionEdit.Text);
    if UpperCase(AppSrvClient1.FunctionCode) = 'SENDFILE' then begin
        FileName := Trim(DataEdit.Text);
        Data := TFileStream.Create(FileName, fmOpenRead + fmShareDenyNone);
        try
            Memo1.Lines.Add('Sending file ''' + FileName + ''' to server (' +
                            IntToStr(Data.Size) + ' bytes)');
            Data.Seek(0, 0);
            AppSrvClient1.Request.WriteFields(TRUE, [ExtractFileName(FileName)]);
            AppSrvClient1.Request.WriteStreamField(FALSE, mwString, Data);
        finally
            Data.Destroy;
        end;
    end
    else begin
        AppSrvClient1.Request.WriteFields(TRUE, [DataEdit.Text, 'abc''def', '123']);
        AppSrvClient1.Request.WriteFields(TRUE, ['delphi']);
    end;
    AppSrvClient1.Port                := PortEdit.Text;
    AppSrvClient1.Server              := ServerEdit.Text;
    AppSrvClient1.SocksPort           := SocksPortEdit.Text;
    AppSrvClient1.SocksServer         := SocksServerEdit.Text;
    AppSrvClient1.SocksUsercode       := SocksUsercodeEdit.Text;
    AppSrvClient1.SocksPassword       := SocksPasswordEdit.Text;
    AppSrvClient1.SocksAuthentication := AuthMethod[SocksAuthCheckBox.Checked];
    AppSrvClient1.Send;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.ImageFormClose(Sender: TObject;
  var Action: TCloseAction);
begin
    Action := caFree;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.DisplayBmpFile;
var
    Form      : TForm;
    Image     : TImage;
    Data      : TFileStream;
    FieldType : TMWFieldType;
    FileName  : String;
begin
    FileName := ExtractFileName(AppSrvClient1.Answer.Fields[0]);
    Memo1.Lines.Add('Displaying image ' + FileName);
    Data := TFileStream.Create(FileName, fmCreate);
    AppSrvClient1.Answer.GetStreamField(1, Data, FieldType);
    Data.Destroy;

    { Just for fun, I create a TForm on the fly with a TImage component }
    Form          := TForm.Create(nil);
    Form.Position := poDefaultPosOnly;
    Form.Width    := Screen.Width div 2;
    Form.Height   := Screen.Height div 2;
    Form.Caption  := FileName;
    Form.OnClose  := ImageFormClose;
    Image         := TImage.Create(Form);
    Image.Parent  := Form;
    Image.Align   := alClient;
    Image.Picture.LoadFromFile(FileName);
    Form.Width    := Image.Picture.Width + Form.Width - Form.ClientWidth;
    Form.Height   := Image.Picture.Height + Form.Height - Form.ClientHeight;
    Form.Show;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.AppSrvClient1RequestDone(
  Sender : TObject;
  Error  : Integer);
var
    nRec : Integer;
begin
    if Error = 0 then begin
        if (FunctionEdit.Text = 'GETFILE') and
           (AppSrvClient1.AnswerStatus = '200') and
           (ExtractFileExt(UpperCase(Trim(DataEdit.Text))) = '.BMP') then
            DisplayBmpFile
        else begin
            Memo1.Lines.Add('Answer status = ' + AppSrvClient1.AnswerStatus);
            nRec := 0;
            AppSrvClient1.Answer.First;
            while not AppSrvClient1.Answer.Eof do begin
                Inc(nRec);
                if Memo1.Lines.Count > 200 then
                    Memo1.Clear;
                Memo1.Lines.Add(IntToStr(nRec) + ': ' +
                                AppSrvClient1.Answer.RecordToString);
                AppSrvClient1.Answer.Next;
            end;
        end;
        if AppSrvClient1.AnswerStatus <> '200'then
            FRepeatFlag := FALSE;
        if FRepeatFlag then begin
            Sleep(500);
            Memo1.Clear;
            SendButtonClick(RepeatButton);
        end;
    end
    else
        Memo1.Lines.Add('Error #' + IntToStr(Error));
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.AppSrvClient1SessionClosed(
  Sender : TObject;
  Error  : Word);
begin
    DisconnectButton.Enabled := FALSE;
    Memo1.Lines.Add('Disconnected.');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.AppSrvClient1SocksConnected(Sender: TObject;
  Error: Word);
begin
    if Error <> 0 then
        Memo1.Lines.Add('Can''t connect to SOCKS server, error #' + IntToStr(Error))
    else
        Memo1.Lines.Add('Connected to SOCKS server');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.AppSrvClient1SocksError(Sender: TObject;
  Error: Integer; Msg: String);
begin
    Memo1.Lines.Add('Socks error #' + IntToStr(Error) + ' : ''' +
                    Msg + '''');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.AppSrvClient1SocksAuthState(Sender: TObject;
  AuthState: TSocksAuthState);
begin
    case AuthState of
    socksAuthStart:
        Memo1.Lines.Add('Socks authentification start.');
    socksAuthSuccess:
        Memo1.Lines.Add('Socks authentification success.');
    socksAuthFailure:
        Memo1.Lines.Add('Socks authentification failure.');
    socksAuthNotRequired:
        Memo1.Lines.Add('Socks authentification not required.');
    else
        Memo1.Lines.Add('Unknown socks authentification state.')
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.AppSrvClient1SessionConnected(Sender: TObject;
  Error: Word);
begin
    if Error <> 0 then
        Memo1.Lines.Add('Can''t connect to applicationserver, error #' +
                        IntToStr(Error))
    else
        Memo1.Lines.Add('Connected to application server');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.AppSrvClient1BannerRcvd(Sender: TObject;
  CmdBuf: PChar; CmdLen: Integer; var BannerOk: Boolean);
begin
    Memo1.Lines.Add('Server banner: ''' + CmdBuf + '''');
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{$IFDEF LZH}
procedure TTestClientForm.AppSrvClient1BeforeProcessReply(Sender: TObject;
  var CmdBuf: PChar; var CmdLen: Integer);
var
    Dst    : PChar;
    DstLen : LongInt;
begin
    { Check if we have some encrypted data }
    FEncryptFlag := not ((CmdLen < 3) or (CmdBuf[0] <> #$FF));
    if not FEncryptFlag then
        Exit;

    { We've got encrypted data. Decrypt. First byte is a flag, ignore. }
    Decrypt(CmdBuf + 1, CmdLen - 1, Dst, DstLen);
    CmdBuf := Dst;
    CmdLen := DstLen;
end;
{$ELSE}
procedure TTestClientForm.AppSrvClient1BeforeProcessReply(Sender: TObject;
  var CmdBuf: PChar; var CmdLen: Integer);
var
    Cnt : Integer;
begin
    { Check if we have some encrypted data }
    if (CmdLen < 3) or (CmdBuf[0] <> #3) then
        Exit;

    { We've got encrypted data. Decrypt on same place. }
    Decrypt(CmdBuf, CmdLen, CmdBuf, Cnt);

    CmdLen := Cnt;
end;
{$ENDIF}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{$IFDEF LZH}
procedure TTestClientForm.AppSrvClient1AfterProcessReply(Sender: TObject;
  var CmdBuf: PChar; var CmdLen: Integer);
begin
    if FEncryptFlag then
        FreeMem(CmdBuf, CmdLen);
end;
{$ELSE}
procedure TTestClientForm.AppSrvClient1AfterProcessReply(Sender: TObject;
  var CmdBuf: PChar; var CmdLen: Integer);
begin
    // Nothing to do
end;
{$ENDIF}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{$IFDEF LZH}
procedure TTestClientForm.AppSrvClient1BeforeSendRequest(Sender: TObject);
var
    Dst    : PChar;
    DstLen : LongInt;
begin
    if not EncryptCheckBox.Checked then   // 16/04/99
        Exit;
    Encrypt(AppSrvClient1.RequestHeader, AppSrvClient1.RequestHeaderLen,
            AppSrvClient1.RequestBody,   AppSrvClient1.RequestBodyLen,
            Dst, DstLen, 1);
    Dst[0] := #$FF;
    AppSrvClient1.RequestHeader    := Dst;
    AppSrvClient1.RequestHeaderLen := DstLen;
    AppSrvClient1.RequestBody      := nil;
    AppSrvClient1.RequestBodyLen   := 0;
end;
{$ELSE}
procedure TTestClientForm.AppSrvClient1BeforeSendRequest(Sender: TObject);
var
    Dst    : PChar;
    DstLen : Integer;
    Key    : Integer;
begin
    if not EncryptCheckBox.Checked then
        Exit;
    Key := Ord('0');
    { Encrypt will allocate new memory for encrypted data which takes a }
    { little bit more space than original data.                         }
    { Memory will be freed in the OnAfterSendRequest event handler.     }
    Encrypt(AppSrvClient1.RequestHeader, AppSrvClient1.RequestHeaderLen,
            Dst, DstLen, Key, 2);
    AppSrvClient1.RequestHeader    := Dst;
    AppSrvClient1.RequestHeaderLen := DstLen;
    Dst[0] := #3;     { This will let the server know we use encrypted data }
    Dst[1] := Chr(Key);
    Encrypt(AppSrvClient1.RequestBody, AppSrvClient1.RequestBodyLen,
            Dst, DstLen, Key, 0);
    AppSrvClient1.RequestBody    := Dst;
    AppSrvClient1.RequestBodyLen := DstLen;
end;
{$ENDIF}


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.AppSrvClient1AfterSendRequest(Sender: TObject);
begin
    if not EncryptCheckBox.Checked then
        Exit;

    { Memory was allocated in the OnBeforeSendRequest event handler. We have }
    { to free it to avoid memory leaks.                                      }
    if AppSrvClient1.RequestHeaderLen > 0 then
        FreeMem(AppSrvClient1.RequestHeader, AppSrvClient1.RequestHeaderLen);
    if AppSrvClient1.RequestBodyLen > 0 then
        FreeMem(AppSrvClient1.RequestBody,   AppSrvClient1.RequestBodyLen);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TTestClientForm.RepeatButtonClick(Sender: TObject);
begin
    FRepeatCount               := 0;
    SendButtonClick(RepeatButton);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.

