program SrvDemo;

uses
  Forms,
  SrvDemo1 in 'SrvDemo1.pas' {SrvDemoForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TSrvDemoForm, SrvDemoForm);
  Application.Run;
end.
