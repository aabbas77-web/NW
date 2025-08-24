program SrvTst;

uses
  Forms,
  SrvTst1 in 'SrvTst1.pas' {ServerForm},
  SrvObj1 in 'SrvObj1.pas',
  SrvObj2 in 'SrvObj2.pas',
  SrvTst2 in 'SrvTst2.pas',
  SrvObj4 in 'SrvObj4.pas',
  SrvObj5 in 'SrvObj5.pas',
  SrvObj3 in 'SrvObj3.pas',
  SrvObj6 in 'SrvObj6.pas',
  SrvObj7 in 'SrvObj7.pas',
  SrvObj8 in 'SrvObj8.pas',
  SrvObj9 in 'SrvObj9.pas',
  SrvObj10 in 'SrvObj10.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TServerForm, ServerForm);
  Application.Run;
end.
