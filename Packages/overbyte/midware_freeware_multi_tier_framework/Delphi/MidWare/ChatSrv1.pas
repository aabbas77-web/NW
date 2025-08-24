{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Author:       François PIETTE
Description:  Simple Chat Server using MidWare. Works with ChatCli.
Creation:     June 19, 1998
Version:      1.01
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

How does it works ?
-------------------

ChatCli works with ChatSrv. Many ChatCli programs connect to one single ChatSrv
program which act as a central server. Each ChatCli log on ChatSrv, identifying
itself with a username (or nickname if you like most). ChatSrv maintain a list
of all connected ChatCli with their respective username and IP address. ChatSrv
serve as a dispatcher between all clients. Each message went by a client to
another client pass thru the server. In other words, a client send a message to
ChatSrv, telling him that the mesage is for some other client. ChatSrv will then
find the destination client and forward the message to him.

Each ChatCli program is also a small server because each ChatCli has to receive
messages sent by the others. If ChatCli was not a server, then he would poll the
main server to know if some message is arrived for him. Being also a server,
chatCli simply stand there waiting for ChatSrv to connect to send any message
from other clients.

ChatSrv support a special username: 'SERVER'. It takes all messages sent to
this user for himself, executing special requests such as 'WHOAMI' and 'WHO'
and replies to the requesting user.

Updates:
Jul 08, 1998  V1.01 Adapted for Delphi 4


 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
unit ChatSrv1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  IniFiles, WSocket, Menus, StdCtrls, ExtCtrls,
  ApServer, ApsCli, ApSrvCli, RFormat, RBroker;

const
  WM_APPSTARTUP = WM_USER + 1;

type
  TDisplayEvent = procedure (Sender: TObject; Msg: String) of object;

  { This record is all the informations we need to hold for each client }
  TChatUser = record
      Name   : String;           { The client nick name                }
      IP     : String;           { The client IP address               }
      Port   : String;           { The client server port number       }
      Client : TClientWSocket;   { The client object inside the server }
  end;
  PChatUser = ^TChatUser;

  { TUserData is a shared object which hold all informations and data }
  { processing common to all TServerObject and the server main code   }
  TUserData = class(TObject)
  private
      FOnDisplay : TDisplayEvent;
  protected
      procedure TriggerDisplay(Msg : String);
  public
      { We hold all connected client into a list. The list items are }
      { TChatUser object references                                  }
      UserList : TList;
      constructor Create; virtual;
      destructor  Destroy; override;
      { The LogonUser procedure will add a new user to the list }
      procedure   LogonUser(UserName  : String;
                            IPAddr    : String;
                            Client    : TClientWSocket;
                            ReplyPort : String);
      { Find a user into the user list, using the username as a key }
      { Returns a user ID which is simply the index into UserList   }
      function    FindUser(UserName : String) : Integer;
      { Find a client into the userlist, using the client object as a key }
      { Returns a user ID which is simply the index into UserList         }
      function    FindClient(Client : TClientWSocket) : Integer;
      { Get the name for a given user ID }
      function    GetName(ID : Integer) : String;
      { Get the IP address for a given user ID }
      function    GetIP(ID : Integer) : String;
      { Get the client's server port number for a given user ID }
      function    GetPort(ID : Integer) : String;
      { Remove a client from the user list }
      procedure   RemoveClient(Client : TClientWSocket);
      { Event to display messages into the server user interface }
      property    OnDisplay : TDisplayEvent read FOnDisplay write FOnDisplay;
  end;

  { The LOGON request is received at the start of the communication. }
  { It is used to record the user into the user list.                }
  TServerObjectLOGON = class(TServerObject)
  public
    procedure Execute; override;
  end;

  { The MESSAGETO request is use to forward a message from a user to }
  { another user.                                                    }
  TServerObjectMESSAGETO = class(TServerObject)
  private
    procedure ExecuteServiceMessages(UserID : Integer; Data : TStream);
    procedure SendMessageRequestDone(Sender: TObject; Error: Integer);
  public
    procedure Execute; override;
  end;

  TChatSrvForm = class(TForm)
    DisplayMemo: TMemo;
    Panel1: TPanel;
    ClientCountLabel: TLabel;
    ObjectCountLabel: TLabel;
    DisconnectAllButton: TButton;
    RequestBroker1: TRequestBroker;
    AppServer1: TAppServer;
    Label1: TLabel;
    Label2: TLabel;
    ClearButton: TButton;
    FunctionsButton: TButton;
    ListClientsButton: TButton;
    procedure FormShow(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure DisconnectAllButtonClick(Sender: TObject);
    procedure AppServer1ClientConnected(Sender: TObject; CliWSocket : TClientWSocket);
    procedure AppServer1ClientClosed(Sender: TObject; CliWSocket : TClientWSocket);
    procedure AppServer1Display(Sender: TObject; Msg: String);
    procedure AppServer1ClientCommand(Sender: TObject;
      CliWSocket: TClientWSocket; CmdBuf: PChar; CmdLen: Integer);
    procedure RequestBroker1ObjCreate(Sender: TObject;
      ServerObject: TServerObject);
    procedure RequestBroker1ObjDestroy(Sender: TObject;
      ServerObject: TServerObject);
    procedure ClearButtonClick(Sender: TObject);
    procedure FunctionsButtonClick(Sender: TObject);
    procedure ListClientsButtonClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  private
    { Déclarations privées }
    FInitialized   : Boolean;
    FIniFileName   : String;
    FPort          : String;
    FUserData      : TUserData;
    procedure WMAppStartup(var msg: TMessage); message WM_APPSTARTUP;
    function  EnumServerFunctions(Sender: TObject;
                                  FunctionCode : String) : boolean;
  end;


var
  ChatSrvForm: TChatSrvForm;

implementation

{$R *.DFM}

const
    MainTitle     = 'MidWare Chat Server - http://www.rtfm.be/fpiette';
    SectionData   = 'Data';
    KeyPort       = 'Port';
    SectionWindow = 'Window';
    KeyTop        = 'Top';
    KeyLeft       = 'Left';
    KeyWidth      = 'Width';
    KeyHeight     = 'Height';

{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatSrvForm.FormCreate(Sender: TObject);
begin
    { Build Ini file name }
    FIniFileName := LowerCase(ExtractFileName(Application.ExeName));
    FIniFileName := Copy(FIniFileName, 1, Length(FIniFileName) - 3) + 'ini';

    { Initialize RequestBroker object }
    RequestBroker1.IniFileName := FIniFileName;
    RequestBroker1.AddServerObject(TServerObjectMESSAGETO);
    RequestBroker1.AddServerObject(TServerObjectLOGON);

    { It's a good place to initialize TRequestBroker.UserData with for example }
    { a pointer to a dynamically allocated record or to an object.             }
    { UserData is passed to ServerObjects instanciated by the broker. Using    }
    { it, they can gain access to some global data or procedure, such as data  }
    { base session.                                                            }

    { In this sample we use a TUserData object }
    FUserData := TUserData.Create;
    FUserData.OnDisplay := AppServer1Display;
    RequestBroker1.UserData := LongInt(FUserData);

    { Initialize user interface }
    ObjectCountLabel.Caption := '0';
    ClientCountLabel.Caption := '0';
    DisplayMemo.Clear;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatSrvForm.FormDestroy(Sender: TObject);
begin
    if Assigned(FUserData) then begin
        FUserData.Free;
        FUserData := nil;
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatSrvForm.FormShow(Sender: TObject);
var
    IniFile : TIniFile;
begin
    if not FInitialized then begin
        FInitialized        := TRUE;
        Caption             := 'Starting ' + MainTitle;

        IniFile := TIniFile.Create(FIniFileName);
        Top    := IniFile.ReadInteger(SectionWindow, KeyTop,
                                      (Screen.Height - Height) div 2);
        Left   := IniFile.ReadInteger(SectionWindow, KeyLeft,
                                      (Screen.Width - Width) div 2);
        Width  := IniFile.ReadInteger(SectionWindow, KeyWidth,  Width);
        Height := IniFile.ReadInteger(SectionWindow, KeyHeight, Height);
        FPort  := IniFile.ReadString(SectionData,    KeyPort,   '2121');
        IniFile.Free;

        { We use a custom message to initialize things once the form }
        { is visible                                                 }
        PostMessage(Handle, WM_APPSTARTUP, 0, 0);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatSrvForm.FormClose(Sender: TObject;
  var Action: TCloseAction);
var
    IniFile : TIniFile;
begin
    AppServer1.Stop;
    AppServer1.DisconnectAll;
    IniFile := TIniFile.Create(FIniFileName);
    IniFile.WriteInteger(SectionWindow, KeyTop,    Top);
    IniFile.WriteInteger(SectionWindow, KeyLeft,   Left);
    IniFile.WriteInteger(SectionWindow, KeyWidth,  Width);
    IniFile.WriteInteger(SectionWindow, KeyHeight, Height);
    IniFile.WriteString(SectionData,    KeyPort,   FPort);
    IniFile.Free;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatSrvForm.DisconnectAllButtonClick(Sender: TObject);
begin
    AppServer1.DisconnectAll;
    ClientCountLabel.Caption := IntToStr(AppServer1.ClientCount);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This message handler is triggered by the FormShow event. We comes here    }
{ only when the form is visible on screen.                                  }
procedure TChatSrvForm.WMAppStartup(var msg: TMessage);
var
    PrvWnd  : HWND;
    Buf     : String;
begin
    { Prevent the server from running twice }
    Buf    := ClassName;
    PrvWnd := FindWindow(PChar(Buf), MainTitle);
    if PrvWnd <> 0 then begin
        Close;
        Exit;
    end;
    Caption := MainTitle;
    Update;                { It's nice to have the form completely displayed }

    { Start the application server component }
    AppServer1.Port := FPort;
    AppServer1.Start;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ A new client has connected, update our user interface                     }
procedure TChatSrvForm.AppServer1ClientConnected(
    Sender     : TObject;
    CliWSocket : TClientWSocket);
begin
    ClientCountLabel.Caption := IntToStr(AppServer1.ClientCount);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ A client has disconnected, update our user interface                      }
procedure TChatSrvForm.AppServer1ClientClosed(
    Sender     : TObject;
    CliWSocket : TClientWSocket);
begin
    FUserData.RemoveClient(CliWSocket);
    ClientCountLabel.Caption := IntToStr(AppServer1.ClientCount - 1);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called when the AppServer component has some info   }
{ to display. This info can comes from one of the server components also.   }
procedure TChatSrvForm.AppServer1Display(Sender: TObject; Msg: String);
begin
    DisplayMemo.Lines.Add(Msg);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called by the AppServer component when a client     }
{ request has been received. We just display it for this demo, but it is    }
{ not a good idea for performance reasons.                                  }
procedure TChatSrvForm.AppServer1ClientCommand(Sender: TObject;
  CliWSocket: TClientWSocket; CmdBuf: PChar; CmdLen: Integer);
begin
    DisplayMemo.Lines.Add(StrPas(CmdBuf));
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called when the object request broker has just      }
{ instanciated a server object to execute a user request.                   }
procedure TChatSrvForm.RequestBroker1ObjCreate(Sender: TObject;
  ServerObject: TServerObject);
begin
    ObjectCountLabel.Caption := IntToStr(RequestBroker1.ObjectCount);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This event handler is called just before the object request broker        }
{ destroy a server object after having executed a user request.             }
procedure TChatSrvForm.RequestBroker1ObjDestroy(Sender: TObject;
  ServerObject: TServerObject);
begin
    ObjectCountLabel.Caption := IntToStr(RequestBroker1.ObjectCount - 1);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatSrvForm.ClearButtonClick(Sender: TObject);
begin
    DisplayMemo.Clear;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ This function is called back by the request broker for each function code }
{ he knows about when we ask to enumerate functions.                        }
function TChatSrvForm.EnumServerFunctions(
    Sender: TObject; FunctionCode : String) : boolean;
begin
    DisplayMemo.Lines.Add(FunctionCode);
    Result := TRUE;   { Continue to enumerate }
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatSrvForm.FunctionsButtonClick(Sender: TObject);
begin
    RequestBroker1.EnumServerFunctions(EnumServerFunctions);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TChatSrvForm.ListClientsButtonClick(Sender: TObject);
var
    UserID : Integer;
begin
    if FUserData.UserList.Count <= 0 then begin
        AppServer1Display(self, 'No connected client');
        Exit;
    end;

    for UserID := 0 to FUserData.UserList.Count - 1 do begin
        AppServer1Display(self,
                          'Name=' + FUserData.GetName(UserID) +
                          ' IP=' + FUserData.GetIP(UserID) +
                          ' Port=' + FUserData.GetPort(UserID));
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
constructor TUserData.Create;
begin
    UserList := TList.Create;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
destructor TUserData.Destroy;
begin
   if Assigned(UserList) then begin
       UserList.Free;
       UserList := nil;
   end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TUserData.TriggerDisplay(Msg : String);
begin
    if Assigned(FOnDisplay) then
        FOnDisplay(Self, Msg);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Find a user into the user list, using the username as a key               }
{ Returns a user ID which is simply the index into UserList                 }
function TUserData.FindUser(UserName : String) : Integer;
var
    I      : Integer;
    User   : PChatUser;
    Name   : String;
begin
    Name   := Trim(Uppercase(UserName));
    for I := 0 to UserList.Count - 1 do begin
        User := PChatUser(UserList.Items[I]);
        if User.Name = Name then begin
            Result := I;
            Exit;
        end;
    end;
    Result := -1;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Find a client into the userlist, using the client object as a key         }
{ Returns a user ID which is simply the index into UserList                 }
function TUserData.FindClient(Client : TClientWSocket) : Integer;
var
    I : Integer;
begin
    for I := 0 to UserList.Count - 1 do begin
        if Client = PChatUser(UserList.Items[I]).Client then begin
            Result := I;
            Exit;
        end;
    end;
    Result := -1;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ Remove a client from the user list                                        }
procedure TUserData.RemoveClient(Client : TClientWSocket);
var
    User   : PChatUser;
    ID     : Integer;
begin
    ID := FindClient(Client);
    if ID >= 0 then begin
        User := UserList.Items[ID];
        TriggerDisplay('LOGOFF: ' + User.Name + ', ' +
                       User.IP + ', ' +
                       IntToHex(Integer(Client), 8) + ', ' +
                       User.Port);
        UserList.Delete(ID);
        Dispose(User);
    end;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TUserData.GetName(ID : Integer) : String;
begin
    Result := PChatUser(UserList.Items[ID])^.Name;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TUserData.GetIP(ID : Integer) : String;
begin
    Result := PChatUser(UserList.Items[ID])^.IP;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
function TUserData.GetPort(ID : Integer) : String;
begin
    Result := PChatUser(UserList.Items[ID])^.Port;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
{ The LogonUser procedure will add a new user to the list provided it is    }
{ not already in the list.                                                  }
procedure TUserData.LogonUser(
    UserName  : String;
    IPAddr    : String;
    Client    : TClientWSocket;
    ReplyPort : String);
var
    ErrMsg : String;
    User   : PChatUser;
    Name   : String;
begin
    Name := Trim(UpperCase(UserName));
    TriggerDisplay('LOGON: ' + UserName + ', ' +
                   IPAddr + ', ' +
                   IntToHex(Integer(Client), 8) + ', ' +
                   ReplyPort);
    { We will check to see if username is at least 4 characters. We don't like }
    { meaningless names...                                                     }
    if Length(Name) < 4 then begin
        ErrMsg := 'Username ''' + UserName + ''' must be at least 4 characters.';
        TriggerDisplay(ErrMsg);
        raise Exception.Create(ErrMsg);
    end;

    { Check for reserved user name }
    if Name = 'SERVER' then begin
        ErrMsg := 'Username ''' + UserName + ''' is reserved.';
        TriggerDisplay(ErrMsg);
        raise Exception.Create(ErrMsg);
    end;

    { Check if the username already exists in the list }
    if FindUser(Name) >= 0 then begin
        ErrMsg := 'Username ''' + UserName + ''' already used.';
        TriggerDisplay(ErrMsg);
        raise Exception.Create(ErrMsg);
    end;

    { Create a new user data record and add it to the end of the list }
    New(User);
    User.Name   := Name;
    User.Client := Client;
    User.IP     := IPAddr;
    User.Port   := ReplyPort;
    UserList.Add(User);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectLOGON.Execute;
var
    UData     : TUserData;
    UserName  : String;
    ReplyPort : String;
    Client    : TClientWSocket;
    IPAddr    : String;
begin
    UData     := TUserData(FUserData);
    UserName  := FRequestBuffer.Fields[0];
    ReplyPort := FRequestBuffer.Fields[1];
    IPAddr    := TClientWSocket(FORBDataPtr.Tag).PeerAddr;
    Client    := TClientWSocket(FORBDataPtr.Tag);
    try
        UData.LogonUser(UserName, IPAddr, Client, ReplyPort);
        FResponseBuffer.WriteFields(TRUE, ['User logged']);
        FResultStatus := 200;
    except
        on E:Exception do begin
            FResponseBuffer.WriteFields(TRUE, ['Logon failed: ' + E.Message]);
            FResultStatus := 401;
        end;
    end;
    Finish;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectMESSAGETO.ExecuteServiceMessages(
    UserID : Integer;
    Data   : TStream);
var
    UData : TUserData;
    Cmd   : String;
    I     : Integer;
    Buf   : String;
begin
    UData    := TUserData(FUserData);
    SetLength(Cmd, Data.Size);
    Data.Read(Cmd[1], Length(Cmd));
    Cmd := Trim(UpperCase(Cmd));

    { Truncate at the first line }
    I := Pos(#13, Cmd);
    if I > 0 then
        SetLength(Cmd, I - 1);

    Data.Size := 0;             { Delete the actual content }
    if Cmd = 'WHOAMI' then begin
        Buf := 'Name=' + UData.GetName(UserID) + ' IP=' + UData.GetIP(UserID);
        Data.Write(Buf[1], Length(Buf));
    end
    else  if Cmd = 'WHO' then begin
        for I := 0 to UData.UserList.Count - 1 do begin
            Buf := 'Name=' + UData.GetName(I) + ' IP=' + UData.GetIP(I) + #13#10;
            Data.Write(Buf[1], Length(Buf));
        end;
    end
    else begin
        Buf := 'Unknown request ''' + Cmd + '''';
        Data.Write(Buf[1], Length(Buf));
    end;

    Data.Seek(0, 0);
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectMESSAGETO.Execute;
var
    UData        : TUserData;
    FromUser     : String;
    ToUser       : String;
    UserId       : Integer;
    AppSrvClient : TAppSrvClient;
    Data         : TMemoryStream;
    FldType      : TMWFieldType;
    IPAddr       : String;
    Port         : String;
begin
    UData    := TUserData(FUserData);
    ToUser   := UpperCase(Trim(FRequestBuffer.Fields[0]));
    FromUser := UpperCase(Trim(FRequestBuffer.Fields[1]));

    { Verify that the sending user has logged on, to avoid fake user }
    UserId := UData.FindUser(FromUser);
    if UserID < 0 then begin
        FResultStatus := 401;
        FResponseBuffer.WriteFields(TRUE, ['''' + FromUser +
                                           ''' must first logon']);
        Finish;
        Exit;
    end;

    { Verify that the sending user still has the same IP, to avoid fake user }
    IPAddr := TClientWSocket(FORBDataPtr.Tag).PeerAddr;
    if IPAddr <> UData.GetIP(UserID) then begin
        FResultStatus := 401;
        FResponseBuffer.WriteFields(TRUE, ['''' + FromUser + ''' has not ' +
                                           'logged with this IP address']);
        Finish;
        Exit;
    end;

    { Search for the destination user }
    if ToUser = 'SERVER' then begin
        IPAddr   := UData.GetIP(UserID);
        Port     := UData.GetPort(UserID);
        FromUser := ToUser;
        UserID   := -2 - UserID;
    end
    else begin
        UserId := UData.FindUser(ToUser);
        if UserID < 0 then begin
            FResultStatus := 401;
            FResponseBuffer.WriteFields(TRUE, ['User ''' + ToUser + ''' not found']);
            Finish;
            Exit;
        end;
        IPAddr := UData.GetIP(UserID);
        Port   := UData.GetPort(UserID);
    end;

    { Now that everything is ok, we must forward the message from the sending }
    { user to the destination user. We will use a dynamically created         }
    { TAppSrvClient to send the message in the background. Remember that each }
    { client has a server part in his program.                                }
    { We have to be very carefull here to avoid memory leaks. Each object     }
    { instanciation or memory allocation must be guraded by a try/finally or  }
    { try/except to be sure to delete the object and free memory in all cases }
    { There are 3 object: a TMemoryStream, a TMWBuffer and a TAppSrvClient    }
    try
        Data := TMemoryStream.Create;
        try
            FRequestBuffer.GetStreamField(2, Data, FldType);
            Data.Seek(0, 0);

            { Check for service messages sent to the server }
            if UserID < -1 then
                ExecuteServiceMessages(-2 - UserID, Data);

            AppSrvClient := TAppSrvClient.Create(nil);
            try
                AppSrvClient.Answer := TMWBuffer.Create(nil);
                try
                    AppSrvClient.FunctionCode := 'MESSAGETO';
                    AppSrvClient.Server       := IPAddr;
                    AppSrvClient.Port         := Port;
                    AppSrvClient.Request.WriteFields(TRUE, [ToUser, FromUser]);
                    AppSrvClient.Request.AppendStreamField(Data, mwBlob);
                    AppSrvClient.OnRequestDone := SendMessageRequestDone;
                    AppSrvClient.Send;
                    { Sending will take place in the background. We must not }
                    { destroy the object if send returns ok. The object will }
                    { be destroyed later, when the request is done, in the   }
                    { SendMessageRequestDone event handler that will be      }
                    { called at that time.                                   }
                except
                    { We got an exception during the request building or     }
                    { when we tried to send. We destroy the TMWBuffer  now   }
                    { and re-raise the exception. It will be catch by the    }
                    { outer try/except to send a negative answer to the      }
                    { originating client.                                    }
                    AppSrvClient.Answer.Free;
                    raise;
                end;
            except
                { We got an exception during the request building or      }
                { when we tried to send. We destroy the TAppSrvClient now }
                { and re-raise the exception. It will be catch by the     }
                { outer try/except to send a negative answer to the       }
                { originating client.                                     }
                AppSrvClient.Free;
                raise;
            end;
        finally
            { We don't need the TMemoryStream. Destroy it now }
            Data.Free;
        end;

        { We arrives here if we where successful in each step before. The }
        { message will be sent in the background. Tell the client that it }
        { is allright.                                                    }
        FResultStatus := 200;
        FResponseBuffer.WriteFields(TRUE, ['Sending message']);
    except
        { Something went wrong before. Use the exception message to built }
        { the answer sent back to the originating client.                 }
        on E:Exception do begin
            FResultStatus := 401;
            FResponseBuffer.Rewrite;
            FResponseBuffer.WriteFields(TRUE, ['Error sending message ' +
                                               E.Message]);
        end;
    end;

    Finish;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}
procedure TServerObjectMESSAGETO.SendMessageRequestDone(
    Sender: TObject;
    Error: Integer);
var
    AppSrvClient : TAppSrvClient;
begin
    AppSrvClient := Sender as TAppSrvClient;
    AppSrvClient.Close;
    AppSrvClient.Answer.Free;
    AppSrvClient.Free;
end;


{* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *}

end.


