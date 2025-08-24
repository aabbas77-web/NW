program BioLife;

uses
  Forms,
  BioLife1 in 'BioLife1.pas' {BioLifeForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TBioLifeForm, BioLifeForm);
  Application.Run;
end.
