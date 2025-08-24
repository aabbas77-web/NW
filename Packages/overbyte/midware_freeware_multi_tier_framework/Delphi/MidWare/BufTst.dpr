program BufTst;

uses
  Forms,
  BufTst1 in 'BufTst1.pas' {BufTstForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TBufTstForm, BufTstForm);
  Application.Run;
end.
