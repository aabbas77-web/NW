program ChatSrv;

uses
  Forms,
  ChatSrv1 in 'ChatSrv1.pas' {ChatSrvForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TChatSrvForm, ChatSrvForm);
  Application.Run;
end.
