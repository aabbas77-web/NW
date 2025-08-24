program TblDemo;

uses
  Forms,
  TblDemo1 in 'TblDemo1.pas' {TblDemoForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TTblDemoForm, TblDemoForm);
  Application.Run;
end.
