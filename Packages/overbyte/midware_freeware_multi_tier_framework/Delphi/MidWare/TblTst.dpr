program TblTst;

uses
  Forms,
  TblTst1 in 'TblTst1.pas' {TblTstForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TTblTstForm, TblTstForm);
  Application.Run;
end.
