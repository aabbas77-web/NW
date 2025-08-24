program CliTst;

uses
  Forms,
  CliTst1 in 'CliTst1.pas' {TestClientForm},
  cipher in 'cipher.pas',
  CipherLz in 'CipherLz.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TTestClientForm, TestClientForm);
  Application.Run;
end.
