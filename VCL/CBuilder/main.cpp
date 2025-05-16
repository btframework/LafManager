//---------------------------------------------------------------------------

#include <vcl.h>
#include <wclErrors.hpp>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifdef _WIN64
	#pragma link "wclCommon.a"
#else
	#pragma link "wclCommon.lib"
#endif
#pragma resource "*.dfm"
#pragma resource "..\\Res\\laf.res"
TfmMain *fmMain;
//---------------------------------------------------------------------------
__fastcall TfmMain::TfmMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormCreate(TObject *Sender)
{
	FLaf = new TwclLafManager();

	int Res = FLaf->Open();
	if (Res != WCL_E_SUCCESS)
		lbLog->Items->Add("Open LAF Manager failed: 0x" + IntToHex(Res, 8));
	else
	{
		lbLog->Items->Add("LAF Manager opened");
		String Pfn = "";
		String AppName = "";
		String Publisher = "";
		Res = FLaf->GetIdentity(Pfn, AppName, Publisher);
		if (Res != WCL_E_SUCCESS)
			lbLog->Items->Add("Get identity failed: 0x" + IntToHex(Res, 8));
		else
		{
			lbLog->Items->Add("PFN: " + Pfn);
			lbLog->Items->Add("AppName: " + AppName);
			lbLog->Items->Add("Publisher: " + Publisher);

			TStringList* Laf = new TStringList();

			Res = FLaf->Enum(Laf);
			if (Res != WCL_E_SUCCESS)
				lbLog->Items->Add("Enum LAF failed: 0x" + IntToHex(Res, 8));
			else
			{
				if (Laf->Count > 0)
				{
					for (int i = 0; i < Laf->Count; i++)
						cbLaf->Items->Add(Laf->Strings[i]);

					cbLaf->ItemIndex = 0;
				}
			}
			Laf->Free();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::FormDestroy(TObject *Sender)
{
	FLaf->Free();
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::btUnlockClick(TObject *Sender)
{
	if (cbLaf->ItemIndex == -1)
		lbLog->Items->Add("No LAF found");
	else
	{
		String Laf = cbLaf->Text;
		int Res = FLaf->Unlock(Laf);
		if (Res != WCL_E_SUCCESS)
			lbLog->Items->Add("Unlock " + Laf + " failed: 0x" + IntToHex(Res, 8));
		else
			lbLog->Items->Add("LAF " + Laf + " unlocked");
	}
}
//---------------------------------------------------------------------------

