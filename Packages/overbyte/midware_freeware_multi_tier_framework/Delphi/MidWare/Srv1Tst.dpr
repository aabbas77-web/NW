program Srv1Tst;

uses
  Forms,
  Srv1Tst1 in 'Srv1Tst1.pas' {SigServerForm},
  SrvObj1 in 'SrvObj1.pas',
  Srv1Tst2 in 'Srv1Tst2.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TSigServerForm, SigServerForm);
  Application.Run;
end.
