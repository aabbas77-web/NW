program ChatCli;

uses
  Forms,
  ChatCli1 in 'ChatCli1.pas' {ChatClientForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TChatClientForm, ChatClientForm);
  Application.Run;
end.
