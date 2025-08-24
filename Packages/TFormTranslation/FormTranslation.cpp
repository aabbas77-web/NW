//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "FormTranslation.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TFormTranslation *)
{
	new TFormTranslation(NULL);
}
//---------------------------------------------------------------------------
namespace Formtranslation
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TFormTranslation)};
		RegisterComponents("WWPTC", classes, 0);
	}
}
//---------------------------------------------------------------------------
__fastcall TFormTranslation::TFormTranslation(TComponent* Owner)
	: TComponent(Owner)
{
	m_nOriginalLanguageID = 0;
	m_nLanguageID = 1;
    m_bGenerate = true;
    LoadSettings();
    if(!ComponentState.Contains(csDesigning))
    {
	    Translate(Owner);
    }
}
//---------------------------------------------------------------------------
__fastcall TFormTranslation::~TFormTranslation()
{
	SaveSettings();
}
//---------------------------------------------------------------------------
void __fastcall TFormTranslation::FlipWindow(HWND hWnd)
{
	// Using ANSI versions of GetWindowLong and SetWindowLong because
    // Unicode is not needed for these calls
    long lExStyles = GetWindowLongA(hWnd, GWL_EXSTYLE);
    // the following lines will update the window layout
    lExStyles ^= WS_EX_LAYOUTRTL;       // toggle layout
    lExStyles ^= WS_EX_NOPARENTNOTIFY;       // toggle layout
    SetWindowLongA(hWnd, GWL_EXSTYLE, lExStyles);
    InvalidateRect(hWnd, NULL, TRUE);   // to update layout in the client area
}
//---------------------------------------------------------------------------
void __fastcall TFormTranslation::LoadSettings()
{            
	TIniFile *pIniFile = new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
	m_nOriginalLanguageID = pIniFile->ReadInteger("Language","OriginalID",0);
	m_nLanguageID = pIniFile->ReadInteger("Language","ID",0);
    m_bGenerate = pIniFile->ReadBool("Language","Generate",true);
    if(pIniFile)	delete pIniFile;
    pIniFile = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormTranslation::SaveSettings()
{
	TIniFile *pIniFile = new TIniFile(ChangeFileExt(Application->ExeName,".ini"));
    if(!pIniFile->ValueExists("Language","OriginalID"))
		pIniFile->WriteInteger("Language","OriginalID",m_nOriginalLanguageID);
    if(!pIniFile->ValueExists("Language","ID"))
		pIniFile->WriteInteger("Language","ID",m_nLanguageID);
    if(!pIniFile->ValueExists("Language","Generate"))
	    pIniFile->WriteBool("Language","Generate",m_bGenerate);
    if(pIniFile)	delete pIniFile;
    pIniFile = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormTranslation::GenerateTranslations(TComponent *pOwner)
{
	GenerateTranslations(pOwner,0);
	GenerateTranslations(pOwner,1);
	GenerateTranslations(pOwner,2);
}
//---------------------------------------------------------------------------
void __fastcall TFormTranslation::GenerateTranslations(TComponent *pOwner,int nLangID)
{
    AnsiString strFileName = ChangeFileExt(Application->ExeName,"."+FormatFloat("0",nLangID));
	TIniFile *pIniFile = new TIniFile(strFileName);

    TComponent *pComponent;
    TCustomEdit *pCustomEdit;
    TCustomLabel *pCustomLabel;
    TStaticText *pStaticText;
    TLabeledEdit *pLabeledEdit;
    TTabSheet *pTabSheet;
    TSpeedButton *pSpeedButton;
    TButton *pButton;
    TRadioButton *pRadioButton;
    TGroupBox *pGroupBox;
    TRadioGroup *pRadioGroup;
    TDBRadioGroup *pDBRadioGroup;
    TToolButton *pToolButton;
    TMenuItem *pMenuItem;
    TCustomAction *pCustomAction;
    TComboBox *pComboBox;
    TPanel *pPanel;
    TCheckBox *pCheckBox;
    TCheckListBox *pCheckListBox;
    TListBox *pListBox;
    TTreeView *pTreeView;
    TListView *pListView;
    TTabControl *pTabControl;
    TDBCheckBox *pDBCheckBox;
    TDBGrid *pDBGrid;
    TWebButton *pWebButton;
    TWebDataDisplay *pWebDataDisplay;
    TValueListEditor *pValueListEditor;
    TQRLabel *pQRLabel;
    TQRSysData *pQRSysData;
    TDataSet *pDataSet;

    TForm *pForm = dynamic_cast<TForm *>(pOwner);
	if(pForm)
    {
	    if(!pIniFile->ValueExists(pForm->Name,pForm->Name+"_Caption"))
	    	pIniFile->WriteString(pForm->Name,pForm->Name+"_Caption",pForm->Caption);
	    if(!pIniFile->ValueExists(pForm->Name,pForm->Name+"_Hint"))
	    	pIniFile->WriteString(pForm->Name,pForm->Name+"_Hint",pForm->Hint);
    }

    for(int i=0;i<pOwner->ComponentCount;i++)
    {
     	pComponent = pOwner->Components[i];

        pLabeledEdit = dynamic_cast<TLabeledEdit *>(pComponent);
        if(pLabeledEdit)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pLabeledEdit->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pLabeledEdit->Name+"_Caption",pLabeledEdit->EditLabel->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pLabeledEdit->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pLabeledEdit->Name+"_Hint",pLabeledEdit->Hint);
        	if(!pIniFile->ValueExists(pOwner->Name,pLabeledEdit->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pLabeledEdit->Name+"_Static",false);
            continue;
        }

        pCustomEdit = dynamic_cast<TCustomEdit *>(pComponent);
        if(pCustomEdit)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pCustomEdit->Name+"_Text"))
				pIniFile->WriteString(pOwner->Name,pCustomEdit->Name+"_Text",pCustomEdit->Text);
        	if(!pIniFile->ValueExists(pOwner->Name,pCustomEdit->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pCustomEdit->Name+"_Hint",pCustomEdit->Hint);
        	if(!pIniFile->ValueExists(pOwner->Name,pCustomEdit->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pCustomEdit->Name+"_Static",false);
            continue;
        }

        pQRLabel = dynamic_cast<TQRLabel *>(pComponent);
        if(pQRLabel)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pQRLabel->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pQRLabel->Name+"_Caption",pQRLabel->Caption);
            continue;
        }

        pQRSysData = dynamic_cast<TQRSysData *>(pComponent);
        if(pQRSysData)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pQRSysData->Name+"_Text"))
				pIniFile->WriteString(pOwner->Name,pQRSysData->Name+"_Text",pQRSysData->Text);
            continue;
        }

        pComboBox = dynamic_cast<TComboBox *>(pComponent);
        if(pComboBox)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pComboBox->Name+"_Text"))
				pIniFile->WriteString(pOwner->Name,pComboBox->Name+"_Text",pComboBox->Text);
        	if(!pIniFile->ValueExists(pOwner->Name,pComboBox->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pComboBox->Name+"_Hint",pComboBox->Hint);
        	if(!pIniFile->ValueExists(pOwner->Name,pComboBox->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pComboBox->Name+"_Static",false);

            for(int i=0;i<pComboBox->Items->Count;i++)
            {
	        	if(!pIniFile->ValueExists(pOwner->Name,pComboBox->Name+"_Caption"+FormatFloat("_00",i)))
					pIniFile->WriteString(pOwner->Name,pComboBox->Name+"_Caption"+FormatFloat("_00",i),pComboBox->Items->Strings[i]);
            }
            continue;
        }

        pDataSet = dynamic_cast<TDataSet *>(pComponent);
        if(pDataSet)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pDataSet->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pDataSet->Name+"_Static",false);

            for(int i=0;i<pDataSet->Fields->Count;i++)
            {
	        	if(!pIniFile->ValueExists(pOwner->Name,pDataSet->Name+"_Caption"+FormatFloat("_00",i)))
					pIniFile->WriteString(pOwner->Name,pDataSet->Name+"_Caption"+FormatFloat("_00",i),pDataSet->Fields->Fields[i]->DisplayLabel);
            }
            continue;
        }

        pDBGrid = dynamic_cast<TDBGrid *>(pComponent);
        if(pDBGrid)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pDBGrid->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pDBGrid->Name+"_Hint",pDBGrid->Hint);
        	if(!pIniFile->ValueExists(pOwner->Name,pDBGrid->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pDBGrid->Name+"_Static",false);

            for(int i=0;i<pDBGrid->Columns->Count;i++)
            {
	        	if(!pIniFile->ValueExists(pOwner->Name,pDBGrid->Name+"_Caption"+FormatFloat("_00",i)))
					pIniFile->WriteString(pOwner->Name,pDBGrid->Name+"_Caption"+FormatFloat("_00",i),pDBGrid->Columns->Items[i]->Title->Caption);
            }
            continue;
        }

        pValueListEditor = dynamic_cast<TValueListEditor *>(pComponent);
        if(pValueListEditor)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pValueListEditor->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pValueListEditor->Name+"_Static",false);

            for(int i=1;i<pValueListEditor->RowCount;i++)
            {
	        	if(!pIniFile->ValueExists(pOwner->Name,pValueListEditor->Cells[0][i]))
					pIniFile->WriteString(pOwner->Name,pValueListEditor->Cells[0][i],pValueListEditor->Cells[1][i]);
            }
            continue;
        }

        pCustomLabel = dynamic_cast<TCustomLabel *>(pComponent);
        if(pCustomLabel)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pCustomLabel->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pCustomLabel->Name+"_Caption",pCustomLabel->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pCustomLabel->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pCustomLabel->Name+"_Hint",pCustomLabel->Hint);
            continue;
        }

        pStaticText = dynamic_cast<TStaticText *>(pComponent);
        if(pStaticText)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pStaticText->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pStaticText->Name+"_Caption",pStaticText->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pStaticText->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pStaticText->Name+"_Hint",pStaticText->Hint);
            continue;
        }

        pTabSheet = dynamic_cast<TTabSheet *>(pComponent);
        if(pTabSheet)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pTabSheet->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pTabSheet->Name+"_Caption",pTabSheet->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pTabSheet->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pTabSheet->Name+"_Hint",pTabSheet->Hint);
            continue;
        }

        pSpeedButton = dynamic_cast<TSpeedButton *>(pComponent);
        if(pSpeedButton)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pSpeedButton->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pSpeedButton->Name+"_Caption",pSpeedButton->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pSpeedButton->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pSpeedButton->Name+"_Hint",pSpeedButton->Hint);
            continue;
        }

        pToolButton = dynamic_cast<TToolButton *>(pComponent);
        if(pToolButton)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pToolButton->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pToolButton->Name+"_Caption",pToolButton->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pToolButton->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pToolButton->Name+"_Hint",pToolButton->Hint);
            continue;
        }

        pCheckBox = dynamic_cast<TCheckBox *>(pComponent);
        if(pCheckBox)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pCheckBox->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pCheckBox->Name+"_Caption",pCheckBox->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pCheckBox->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pCheckBox->Name+"_Hint",pCheckBox->Hint);
            continue;
        }

        pDBCheckBox = dynamic_cast<TDBCheckBox *>(pComponent);
        if(pDBCheckBox)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pDBCheckBox->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pDBCheckBox->Name+"_Caption",pDBCheckBox->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pDBCheckBox->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pDBCheckBox->Name+"_Hint",pDBCheckBox->Hint);
            continue;
        }

        pButton = dynamic_cast<TButton *>(pComponent);
        if(pButton)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pButton->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pButton->Name+"_Caption",pButton->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pButton->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pButton->Name+"_Hint",pButton->Hint);
            continue;
        }

        pRadioButton = dynamic_cast<TRadioButton *>(pComponent);
        if(pRadioButton)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pRadioButton->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pRadioButton->Name+"_Caption",pRadioButton->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pRadioButton->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pRadioButton->Name+"_Hint",pRadioButton->Hint);
            continue;
        }

        pGroupBox = dynamic_cast<TGroupBox *>(pComponent);
        if(pGroupBox)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pGroupBox->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pGroupBox->Name+"_Caption",pGroupBox->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pGroupBox->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pGroupBox->Name+"_Hint",pGroupBox->Hint);
            continue;
        }

        pRadioGroup = dynamic_cast<TRadioGroup *>(pComponent);
        if(pRadioGroup)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pRadioGroup->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pRadioGroup->Name+"_Caption",pRadioGroup->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pRadioGroup->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pRadioGroup->Name+"_Hint",pRadioGroup->Hint);
        	if(!pIniFile->ValueExists(pOwner->Name,pRadioGroup->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pRadioGroup->Name+"_Static",false);

            for(int i=0;i<pRadioGroup->Items->Count;i++)
            {
	        	if(!pIniFile->ValueExists(pOwner->Name,pRadioGroup->Name+"_Caption"+FormatFloat("_00",i)))
					pIniFile->WriteString(pOwner->Name,pRadioGroup->Name+"_Caption"+FormatFloat("_00",i),pRadioGroup->Items->Strings[i]);
            }
            continue;
        }

        pCheckListBox = dynamic_cast<TCheckListBox *>(pComponent);
        if(pCheckListBox)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pCheckListBox->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pCheckListBox->Name+"_Static",false);
            for(int i=0;i<pCheckListBox->Items->Count;i++)
            {
	        	if(!pIniFile->ValueExists(pOwner->Name,pCheckListBox->Name+"_Caption"+FormatFloat("_00",i)))
					pIniFile->WriteString(pOwner->Name,pCheckListBox->Name+"_Caption"+FormatFloat("_00",i),pCheckListBox->Items->Strings[i]);
            }
            continue;
        }

        pListBox = dynamic_cast<TListBox *>(pComponent);
        if(pListBox)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pListBox->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pListBox->Name+"_Static",false);
            for(int i=0;i<pListBox->Items->Count;i++)
            {
	        	if(!pIniFile->ValueExists(pOwner->Name,pListBox->Name+"_Caption"+FormatFloat("_00",i)))
					pIniFile->WriteString(pOwner->Name,pListBox->Name+"_Caption"+FormatFloat("_00",i),pListBox->Items->Strings[i]);
            }
            continue;
        }

        pTreeView = dynamic_cast<TTreeView *>(pComponent);
        if(pTreeView)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pTreeView->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pTreeView->Name+"_Static",false);
            for(int i=0;i<pTreeView->Items->Count;i++)
            {
	        	if(!pIniFile->ValueExists(pOwner->Name,pTreeView->Name+"_Caption"+FormatFloat("_00",i)))
					pIniFile->WriteString(pOwner->Name,pTreeView->Name+"_Caption"+FormatFloat("_00",i),pTreeView->Items->Item[i]->Text);
            }
            continue;
        }

        pListView = dynamic_cast<TListView *>(pComponent);
        if(pListView)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pListView->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pListView->Name+"_Static",false);
            for(int i=0;i<pListView->Items->Count;i++)
            {
	        	if(!pIniFile->ValueExists(pOwner->Name,pListView->Name+"_Caption"+FormatFloat("_00",i)))
					pIniFile->WriteString(pOwner->Name,pListView->Name+"_Caption"+FormatFloat("_00",i),pListView->Items->Item[i]->Caption);
            }
            continue;
        }

        pTabControl = dynamic_cast<TTabControl *>(pComponent);
        if(pTabControl)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pTabControl->Name+"_Static"))
				pIniFile->WriteBool(pOwner->Name,pTabControl->Name+"_Static",false);
            for(int i=0;i<pTabControl->Tabs->Count;i++)
            {
	        	if(!pIniFile->ValueExists(pOwner->Name,pTabControl->Name+"_Caption"+FormatFloat("_00",i)))
					pIniFile->WriteString(pOwner->Name,pTabControl->Name+"_Caption"+FormatFloat("_00",i),pTabControl->Tabs->Strings[i]);
            }
            continue;
        }

        pDBRadioGroup = dynamic_cast<TDBRadioGroup *>(pComponent);
        if(pDBRadioGroup)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pDBRadioGroup->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pDBRadioGroup->Name+"_Caption",pDBRadioGroup->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pDBRadioGroup->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pDBRadioGroup->Name+"_Hint",pDBRadioGroup->Hint);
            continue;
        }

        pMenuItem = dynamic_cast<TMenuItem *>(pComponent);
        if(pMenuItem)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pMenuItem->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pMenuItem->Name+"_Caption",pMenuItem->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pMenuItem->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pMenuItem->Name+"_Hint",pMenuItem->Hint);
            continue;
        }

        pCustomAction = dynamic_cast<TCustomAction *>(pComponent);
        if(pCustomAction)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pCustomAction->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pCustomAction->Name+"_Caption",pCustomAction->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pCustomAction->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pCustomAction->Name+"_Hint",pCustomAction->Hint);
            continue;
        }

        pPanel = dynamic_cast<TPanel *>(pComponent);
        if(pPanel)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pPanel->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pPanel->Name+"_Caption",pPanel->Caption);
        	if(!pIniFile->ValueExists(pOwner->Name,pPanel->Name+"_Hint"))
				pIniFile->WriteString(pOwner->Name,pPanel->Name+"_Hint",pPanel->Hint);
            continue;
        }

        pWebButton = dynamic_cast<TWebButton *>(pComponent);
        if(pWebButton)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pWebButton->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pWebButton->Name+"_Caption",pWebButton->Caption);
            continue;
        }

        pWebDataDisplay = dynamic_cast<TWebDataDisplay *>(pComponent);
        if(pWebDataDisplay)
        {
        	if(!pIniFile->ValueExists(pOwner->Name,pWebDataDisplay->Name+"_Caption"))
				pIniFile->WriteString(pOwner->Name,pWebDataDisplay->Name+"_Caption",pWebDataDisplay->Caption);
            continue;
        }
    }

    if(pIniFile)	delete pIniFile;
    pIniFile = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormTranslation::FlipAnchor(TControl *pControl)
{
	if(pControl->Anchors.Contains(akLeft) && !pControl->Anchors.Contains(akRight))
    {
		(pControl->Anchors >> akLeft) << akRight;
    }
    else
	if(pControl->Anchors.Contains(akRight) && !pControl->Anchors.Contains(akLeft))
    {
		(pControl->Anchors >> akRight) << akLeft;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormTranslation::Translate(TComponent *pOwner)
{
    AnsiString strLanguageFileName = ChangeFileExt(Application->ExeName,".lng");
	if(m_bGenerate)
    {
		GenerateTranslations(pOwner);
    }
    AnsiString strFileName = ChangeFileExt(Application->ExeName,"."+FormatFloat("0",m_nLanguageID));
    if(!FileExists(strFileName))
    {
    	MessageDlg("Language file not found...\n["+strFileName+"]",mtError,TMsgDlgButtons()<<mbOK,0);
     	return;
    }
	TIniFile *pIniFile = new TIniFile(strFileName);

    TComponent *pComponent;
    TCustomEdit *pCustomEdit;
    TCustomLabel *pCustomLabel;
    TStaticText *pStaticText;
    TLabeledEdit *pLabeledEdit;
    TTabSheet *pTabSheet;
    TSpeedButton *pSpeedButton;
    TToolButton *pToolButton;
    TMenuItem *pMenuItem;
    TCustomAction *pCustomAction;
    TComboBox *pComboBox;
    TCheckBox *pCheckBox;
    TDBCheckBox *pDBCheckBox;
    TDBGrid *pDBGrid;
    TButton *pButton;
    TRadioButton *pRadioButton;
    TGroupBox *pGroupBox;
    TRadioGroup *pRadioGroup;
    TCheckListBox *pCheckListBox;
    TListBox *pListBox;
    TTreeView *pTreeView;
    TListView *pListView;
    TTabControl *pTabControl;
    TDBRadioGroup *pDBRadioGroup;
    TPanel *pPanel;
    TWebButton *pWebButton;
    TWebDataDisplay *pWebDataDisplay;
    TMenu *pMenu;
    TControl *pControl;
    bool IsStatic;
    bool bFlipChildren = false;
    TValueListEditor *pValueListEditor;
    TQRLabel *pQRLabel;
    TQRSysData *pQRSysData;
	TQRPrintable *pQRPrintable;
    TDataSet *pDataSet;

    if( ((m_nLanguageID != 1) && (m_nOriginalLanguageID == 1)) ||
    	((m_nLanguageID == 1) && (m_nOriginalLanguageID != 1)))
    {
		bFlipChildren = true;
    }

    TBiDiMode gBiDiMode = bdLeftToRight;
    AnsiString strDicFile;
    switch(m_nLanguageID)
    {
     	case 0:// English
        {
    		gBiDiMode = bdLeftToRight;
         	break;
        }
     	case 1:// Arabic
        {
    		gBiDiMode = bdRightToLeft;
         	break;
        }
     	case 2:// French
        {
    		gBiDiMode = bdLeftToRight;
         	break;
        }
    }


    TForm *pForm = dynamic_cast<TForm *>(pOwner);
    TFrame *pFrame = dynamic_cast<TFrame *>(pOwner);
	if(pForm)
    {
    	pForm->Caption = pIniFile->ReadString(pForm->Name,pForm->Name+"_Caption",pForm->Caption);
	    pForm->Hint = pIniFile->ReadString(pForm->Name,pForm->Name+"_Hint",pForm->Hint);
	    pForm->BiDiMode = gBiDiMode;
    }
	if(pFrame)
    {
	    pFrame->Hint = pIniFile->ReadString(pFrame->Name,pFrame->Name+"_Hint",pFrame->Hint);
	    pFrame->BiDiMode = gBiDiMode;
    }
//    FlipWindow(pOwner->Handle);

    // USE THIS FOR MIRRORING
//    RECT rControlRect;
//	GetWindowRect(pOwner->Handle, (LPRECT) &rControlRect);
//	MapWindowPoints(NULL, pOwner->Handle, (LPPOINT) &rControlRect, 2);

    for(int i=0;i<pOwner->ComponentCount;i++)
    {
     	pComponent = pOwner->Components[i];

	    if((SameText(pComponent->ClassName(),"TTreeView")) ||
 	       (SameText(pComponent->ClassName(),"TListView")) ||
 	       (SameText(pComponent->ClassName(),"TPageControl")) ||
 	       (SameText(pComponent->ClassName(),"TTabControl")) ||
 	       (SameText(pComponent->ClassName(),"TTabbedNoteBook")) ||
 	       (SameText(pComponent->ClassName(),"TToolBar")))
	    {
//			HWND hWnd = dynamic_cast<TWinControl *>(pComponent)->Handle;

    		if(((m_nLanguageID != 1) && (m_nOriginalLanguageID == 1)) ||
    			((m_nLanguageID == 1) && (m_nOriginalLanguageID != 1)))
		    {
//            	FlipWindow(hWnd);
            }
//            continue;
	    }

        pLabeledEdit = dynamic_cast<TLabeledEdit *>(pComponent);
        if(pLabeledEdit)
        {
			pLabeledEdit->EditLabel->Caption = pIniFile->ReadString(pOwner->Name,pLabeledEdit->Name+"_Caption",pLabeledEdit->EditLabel->Caption);
			pLabeledEdit->Hint = pIniFile->ReadString(pOwner->Name,pLabeledEdit->Name+"_Hint",pLabeledEdit->Hint);
            pLabeledEdit->BiDiMode = gBiDiMode;
    		if(bFlipChildren)
            {
            	FlipAnchor(pLabeledEdit);
            }
            continue;
        }

	    pCustomEdit = dynamic_cast<TCustomEdit *>(pComponent);
    	if(pCustomEdit)
	    {
	        IsStatic = pIniFile->ReadBool(pOwner->Name,pCustomEdit->Name+"_Static",false);
			if(IsStatic)
            {
				pCustomEdit->Text = pIniFile->ReadString(pOwner->Name,pCustomEdit->Name+"_Text",pCustomEdit->Text);
            }
			pCustomEdit->Hint = pIniFile->ReadString(pOwner->Name,pCustomEdit->Name+"_Hint",pCustomEdit->Hint);
	        pCustomEdit->BiDiMode = gBiDiMode;
    		if(bFlipChildren)
            {
            	FlipAnchor(pCustomEdit);
            }
	        continue;
	    }

	    pQRLabel = dynamic_cast<TQRLabel *>(pComponent);
    	if(pQRLabel)
	    {
			pQRLabel->Caption = pIniFile->ReadString(pOwner->Name,pQRLabel->Name+"_Caption",pQRLabel->Caption);
	        pQRLabel->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
				pQRLabel->Size->Left = pQRLabel->ParentReport->Bands->TitleBand->Size->Width - pQRLabel->Size->Left - pQRLabel->Size->Width;
            }
	        continue;
	    }

	    pQRSysData = dynamic_cast<TQRSysData *>(pComponent);
    	if(pQRSysData)
	    {
			pQRSysData->Text = pIniFile->ReadString(pOwner->Name,pQRSysData->Name+"_Text",pQRSysData->Text);
	        pQRSysData->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
				pQRSysData->Size->Left = pQRSysData->ParentReport->Bands->TitleBand->Size->Width - pQRSysData->Size->Left - pQRSysData->Size->Width;
            }
	        continue;
	    }

        if(
        	(pComponent->ClassNameIs("TQRDBText")) ||
        	(pComponent->ClassNameIs("TQRExpr")) ||
        	(pComponent->ClassNameIs("TQRMemo")) ||
        	(pComponent->ClassNameIs("TQRExprMemo")) ||
        	(pComponent->ClassNameIs("TQRRichText")) ||
        	(pComponent->ClassNameIs("TQRDBRichText")) ||
        	(pComponent->ClassNameIs("TQRShape")) ||
        	(pComponent->ClassNameIs("TQRImage")) ||
        	(pComponent->ClassNameIs("TQRDBImage")) ||
        	(pComponent->ClassNameIs("TQRChart"))
          )
        {
        	pQRPrintable = dynamic_cast<TQRPrintable *>(pComponent); 
	    	if(pQRPrintable)
		    {
		        pQRPrintable->BiDiMode = gBiDiMode;
	            if(bFlipChildren)
	            {
					pQRPrintable->Size->Left = pQRPrintable->ParentReport->Bands->TitleBand->Size->Width - pQRPrintable->Size->Left - pQRPrintable->Size->Width;
	            }
		        continue;
		    }
        }

	    pComboBox = dynamic_cast<TComboBox *>(pComponent);
	    if(pComboBox)
	    {
			pComboBox->Text = pIniFile->ReadString(pOwner->Name,pComboBox->Name+"_Text",pComboBox->Text);
			pComboBox->Hint = pIniFile->ReadString(pOwner->Name,pComboBox->Name+"_Hint",pComboBox->Hint);
	        pComboBox->BiDiMode = gBiDiMode;
	        IsStatic = pIniFile->ReadBool(pOwner->Name,pComboBox->Name+"_Static",false);
			if(IsStatic)
            {
		        for(int i=0;i<pComboBox->Items->Count;i++)
		        {
					pComboBox->Items->Strings[i] = pIniFile->ReadString(pOwner->Name,pComboBox->Name+"_Caption"+FormatFloat("_00",i),pComboBox->Items->Strings[i]);
	    	    }
            }
            if(bFlipChildren)
            {
            	FlipAnchor(pComboBox);
            }
	        continue;
	    }

        pDataSet = dynamic_cast<TDataSet *>(pComponent);
        if(pDataSet)
        {
	        IsStatic = pIniFile->ReadBool(pOwner->Name,pDataSet->Name+"_Static",false);
			if(IsStatic)
            {
	            for(int i=0;i<pDataSet->Fields->Count;i++)
		        {
					pDataSet->Fields->Fields[i]->DisplayLabel = pIniFile->ReadString(pOwner->Name,pDataSet->Name+"_Caption"+FormatFloat("_00",i),pDataSet->Fields->Fields[i]->DisplayLabel);
	    	    }
            }
            continue;
        }

        pDBGrid = dynamic_cast<TDBGrid *>(pComponent);
        if(pDBGrid)
        {
			pDBGrid->Hint = pIniFile->ReadString(pOwner->Name,pDBGrid->Name+"_Hint",pDBGrid->Hint);
	        pDBGrid->BiDiMode = gBiDiMode;
	        IsStatic = pIniFile->ReadBool(pOwner->Name,pDBGrid->Name+"_Static",false);
			if(IsStatic)
            {
	            for(int i=0;i<pDBGrid->Columns->Count;i++)
		        {
					pDBGrid->Columns->Items[i]->Title->Caption = pIniFile->ReadString(pOwner->Name,pDBGrid->Name+"_Caption"+FormatFloat("_00",i),pDBGrid->Columns->Items[i]->Title->Caption);
	    	    }
            }
            if(bFlipChildren)
            {
            	FlipAnchor(pDBGrid);
            }
            continue;
        }

	    pValueListEditor = dynamic_cast<TValueListEditor *>(pComponent);
	    if(pValueListEditor)
	    {
	        IsStatic = pIniFile->ReadBool(pOwner->Name,pValueListEditor->Name+"_Static",false);
			if(IsStatic)
            {
	        	for(int i=1;i<pValueListEditor->RowCount;i++)
    	        {
        	    	pValueListEditor->Cells[1][i] = pIniFile->ReadString(pOwner->Name,pValueListEditor->Cells[0][i],pValueListEditor->Cells[1][i]);
            	}
            }
            if(bFlipChildren)
            {
            	FlipAnchor(pValueListEditor);
            }
	        continue;
	    }

        pCustomLabel = dynamic_cast<TCustomLabel *>(pComponent);
        if(pCustomLabel)
        {
			pCustomLabel->Caption = pIniFile->ReadString(pOwner->Name,pCustomLabel->Name+"_Caption",pCustomLabel->Caption);
			pCustomLabel->Hint = pIniFile->ReadString(pOwner->Name,pCustomLabel->Name+"_Hint",pCustomLabel->Hint);
            pCustomLabel->BiDiMode = gBiDiMode;
////////////////////////////////////////////////////////////////////////////////
//////////////// BY FERAS //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/* 
            if ( pCustomLabel->Align == alLeft )
            {
              pCustomLabel->Align = alRight;
            }
            else
            {
              if ( pCustomLabel->Align == alRight )
              {
                pCustomLabel->Align = alLeft;
              }
            }
*/
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
            if(bFlipChildren)
            {
            	FlipAnchor(pCustomLabel);
            }
            continue;
        }

        pStaticText = dynamic_cast<TStaticText *>(pComponent);
        if(pStaticText)
        {
			pStaticText->Caption = pIniFile->ReadString(pOwner->Name,pStaticText->Name+"_Caption",pStaticText->Caption);
			pStaticText->Hint = pIniFile->ReadString(pOwner->Name,pStaticText->Name+"_Hint",pStaticText->Hint);
            pStaticText->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pStaticText);
            }
            continue;
        }

        pTabSheet = dynamic_cast<TTabSheet *>(pComponent);
        if(pTabSheet)
        {
			pTabSheet->Caption = pIniFile->ReadString(pOwner->Name,pTabSheet->Name+"_Caption",pTabSheet->Caption);
			pTabSheet->Hint = pIniFile->ReadString(pOwner->Name,pTabSheet->Name+"_Hint",pTabSheet->Hint);
            pTabSheet->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pTabSheet); 
            }
            continue;
        }

        pSpeedButton = dynamic_cast<TSpeedButton *>(pComponent);
        if(pSpeedButton)
        {
			pSpeedButton->Caption = pIniFile->ReadString(pOwner->Name,pSpeedButton->Name+"_Caption",pSpeedButton->Caption);
			pSpeedButton->Hint = pIniFile->ReadString(pOwner->Name,pSpeedButton->Name+"_Hint",pSpeedButton->Hint);
            pSpeedButton->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pSpeedButton);
            }
            continue;
        }

        pToolButton = dynamic_cast<TToolButton *>(pComponent);
        if(pToolButton)
        {
			pToolButton->Caption = pIniFile->ReadString(pOwner->Name,pToolButton->Name+"_Caption",pToolButton->Caption);
			pToolButton->Hint = pIniFile->ReadString(pOwner->Name,pToolButton->Name+"_Hint",pToolButton->Hint);
            pToolButton->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pToolButton);
            }
            continue;
        }

        pCheckBox = dynamic_cast<TCheckBox *>(pComponent);
        if(pCheckBox)
        {
			pCheckBox->Caption = pIniFile->ReadString(pOwner->Name,pCheckBox->Name+"_Caption",pCheckBox->Caption);
			pCheckBox->Hint = pIniFile->ReadString(pOwner->Name,pCheckBox->Name+"_Hint",pCheckBox->Hint);
            pCheckBox->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pCheckBox);
            }
            continue;
        }

        pDBCheckBox = dynamic_cast<TDBCheckBox *>(pComponent);
        if(pDBCheckBox)
        {
			pDBCheckBox->Caption = pIniFile->ReadString(pOwner->Name,pDBCheckBox->Name+"_Caption",pDBCheckBox->Caption);
			pDBCheckBox->Hint = pIniFile->ReadString(pOwner->Name,pDBCheckBox->Name+"_Hint",pDBCheckBox->Hint);
            pDBCheckBox->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pDBCheckBox);
            }
            continue;
        }

        pButton = dynamic_cast<TButton *>(pComponent);
        if(pButton)
        {
			pButton->Caption = pIniFile->ReadString(pOwner->Name,pButton->Name+"_Caption",pButton->Caption);
			pButton->Hint = pIniFile->ReadString(pOwner->Name,pButton->Name+"_Hint",pButton->Hint);
            pButton->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pButton);
            }
            continue;
        }

        pRadioButton = dynamic_cast<TRadioButton *>(pComponent);
        if(pRadioButton)
        {
			pRadioButton->Caption = pIniFile->ReadString(pOwner->Name,pRadioButton->Name+"_Caption",pRadioButton->Caption);
			pRadioButton->Hint = pIniFile->ReadString(pOwner->Name,pRadioButton->Name+"_Hint",pRadioButton->Hint);
            pRadioButton->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pRadioButton);
            }
            continue;
        }

        pGroupBox = dynamic_cast<TGroupBox *>(pComponent);
        if(pGroupBox)
        {
			pGroupBox->Caption = pIniFile->ReadString(pOwner->Name,pGroupBox->Name+"_Caption",pGroupBox->Caption);
			pGroupBox->Hint = pIniFile->ReadString(pOwner->Name,pGroupBox->Name+"_Hint",pGroupBox->Hint);
            pGroupBox->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pGroupBox);
            }
            continue;
        }

        pRadioGroup = dynamic_cast<TRadioGroup *>(pComponent);
        if(pRadioGroup)
        {
			pRadioGroup->Caption = pIniFile->ReadString(pOwner->Name,pRadioGroup->Name+"_Caption",pRadioGroup->Caption);
			pRadioGroup->Hint = pIniFile->ReadString(pOwner->Name,pRadioGroup->Name+"_Hint",pRadioGroup->Hint);
            pRadioGroup->BiDiMode = gBiDiMode;
            IsStatic = pIniFile->ReadBool(pOwner->Name,pRadioGroup->Name+"_Static",false);
			if(IsStatic)
            {
	            for(int i=0;i<pRadioGroup->Items->Count;i++)
	            {
					pRadioGroup->Items->Strings[i] = pIniFile->ReadString(pOwner->Name,pRadioGroup->Name+"_Caption"+FormatFloat("_00",i),pRadioGroup->Items->Strings[i]);
	            }
            }
            if(bFlipChildren)
            {
            	FlipAnchor(pRadioGroup);
            }
            continue;
        }

        pCheckListBox = dynamic_cast<TCheckListBox *>(pComponent);
        if(pCheckListBox)
        {
            IsStatic = pIniFile->ReadBool(pOwner->Name,pCheckListBox->Name+"_Static",false);
			if(IsStatic)
            {
	            for(int i=0;i<pCheckListBox->Items->Count;i++)
	            {
					pCheckListBox->Items->Strings[i] = pIniFile->ReadString(pOwner->Name,pCheckListBox->Name+"_Caption"+FormatFloat("_00",i),pCheckListBox->Items->Strings[i]);
    	        }
            }
            if(bFlipChildren)
            {
            	FlipAnchor(pCheckListBox);
            }
            continue;
        }

        pListBox = dynamic_cast<TListBox *>(pComponent);
        if(pListBox)
        {
            IsStatic = pIniFile->ReadBool(pOwner->Name,pListBox->Name+"_Static",false);
			if(IsStatic)
            {
	            for(int i=0;i<pListBox->Items->Count;i++)
	            {
					pListBox->Items->Strings[i] = pIniFile->ReadString(pOwner->Name,pListBox->Name+"_Caption"+FormatFloat("_00",i),pListBox->Items->Strings[i]);
    	        }
            }
            if(bFlipChildren)
            {
            	FlipAnchor(pListBox);
            }
            continue;
        }

        pTreeView = dynamic_cast<TTreeView *>(pComponent);
        if(pTreeView)
        {
            IsStatic = pIniFile->ReadBool(pOwner->Name,pTreeView->Name+"_Static",false);
			if(IsStatic)
            {
	            for(int i=0;i<pTreeView->Items->Count;i++)
	            {
					pTreeView->Items->Item[i]->Text = pIniFile->ReadString(pOwner->Name,pTreeView->Name+"_Caption"+FormatFloat("_00",i),pTreeView->Items->Item[i]->Text);
    	        }
            }
            if(bFlipChildren)
            {
            	FlipAnchor(pTreeView);
            }
            continue;
        }

        pListView = dynamic_cast<TListView *>(pComponent);
        if(pListView)
        {
            IsStatic = pIniFile->ReadBool(pOwner->Name,pListView->Name+"_Static",false);
			if(IsStatic)
            {
	            for(int i=0;i<pListView->Items->Count;i++)
	            {
					pListView->Items->Item[i]->Caption = pIniFile->ReadString(pOwner->Name,pListView->Name+"_Caption"+FormatFloat("_00",i),pListView->Items->Item[i]->Caption);
    	        }
            }
            if(bFlipChildren)
            {
            	FlipAnchor(pListView);
            }
            continue;
        }

        pTabControl = dynamic_cast<TTabControl *>(pComponent);
        if(pTabControl)
        {
            IsStatic = pIniFile->ReadBool(pOwner->Name,pTabControl->Name+"_Static",false);
			if(IsStatic)
            {
	            for(int i=0;i<pTabControl->Tabs->Count;i++)
	            {
					pTabControl->Tabs->Strings[i] = pIniFile->ReadString(pOwner->Name,pTabControl->Name+"_Caption"+FormatFloat("_00",i),pTabControl->Tabs->Strings[i]);
    	        }
            }
            if(bFlipChildren)
            {
            	FlipAnchor(pTabControl);
            }
            continue;
        }

        pDBRadioGroup = dynamic_cast<TDBRadioGroup *>(pComponent);
        if(pDBRadioGroup)
        {
			pDBRadioGroup->Caption = pIniFile->ReadString(pOwner->Name,pDBRadioGroup->Name+"_Caption",pDBRadioGroup->Caption);
			pDBRadioGroup->Hint = pIniFile->ReadString(pOwner->Name,pDBRadioGroup->Name+"_Hint",pDBRadioGroup->Hint);
            pDBRadioGroup->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pDBRadioGroup);
            }
            continue;
        }

        pMenuItem = dynamic_cast<TMenuItem *>(pComponent);
        if(pMenuItem)
        {
			pMenuItem->Caption = pIniFile->ReadString(pOwner->Name,pMenuItem->Name+"_Caption",pMenuItem->Caption);
			pMenuItem->Hint = pIniFile->ReadString(pOwner->Name,pMenuItem->Name+"_Hint",pMenuItem->Hint);
            continue;
        }

        pCustomAction = dynamic_cast<TCustomAction *>(pComponent);
        if(pCustomAction)
        {
			pCustomAction->Caption = pIniFile->ReadString(pOwner->Name,pCustomAction->Name+"_Caption",pCustomAction->Caption);
			pCustomAction->Hint = pIniFile->ReadString(pOwner->Name,pCustomAction->Name+"_Hint",pCustomAction->Hint);
            continue;
        }

        pPanel = dynamic_cast<TPanel *>(pComponent);
        if(pPanel)
        {
			pPanel->Caption = pIniFile->ReadString(pOwner->Name,pPanel->Name+"_Caption",pPanel->Caption);
			pPanel->Hint = pIniFile->ReadString(pOwner->Name,pPanel->Name+"_Hint",pPanel->Hint);
            pPanel->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pPanel);
            }
            continue;
        }

        pWebButton = dynamic_cast<TWebButton *>(pComponent);
        if(pWebButton)
        {
			pWebButton->Caption = pIniFile->ReadString(pOwner->Name,pWebButton->Name+"_Caption",pWebButton->Caption);
            continue;
        }

        pWebDataDisplay = dynamic_cast<TWebDataDisplay *>(pComponent);
        if(pWebDataDisplay)
        {
			pWebDataDisplay->Caption = pIniFile->ReadString(pOwner->Name,pWebDataDisplay->Name+"_Caption",pWebDataDisplay->Caption);
            continue;
        }

        pMenu = dynamic_cast<TMenu *>(pComponent);
        if(pMenu)
        {
			pMenu->BiDiMode = gBiDiMode;
            continue;
        }

        pControl = dynamic_cast<TControl *>(pComponent);
        if(pControl)
        {
			pControl->BiDiMode = gBiDiMode;
            if(bFlipChildren)
            {
            	FlipAnchor(pControl);
            }
            continue;
        }
    }

    if(pIniFile)	delete pIniFile;
    pIniFile = NULL;


//    if(SameText(pComponent->ClassName(),"THeaderControl"))
//    {
//		// Bug in FlipChildren so we set it`s visibility to false
//    }

	if(pForm)
    {
		if(bFlipChildren)
	    {
			pForm->FlipChildren(true);
    	}
    }
	if(pFrame)
    {
		if(bFlipChildren)
	    {
			pFrame->FlipChildren(true);
    	}
    }

}
//---------------------------------------------------------------------------

