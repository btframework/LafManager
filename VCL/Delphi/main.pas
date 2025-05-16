unit main;

interface

uses
  Vcl.Forms, wclLaf, Vcl.Controls, Vcl.StdCtrls, System.Classes;

type
  TfmMain = class(TForm)
    laAvailableLaf: TLabel;
    cbLaf: TComboBox;
    btUnlock: TButton;
    lbLog: TListBox;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure btUnlockClick(Sender: TObject);

  private
    FLaf: TwclLafManager;
  end;

var
  fmMain: TfmMain;

implementation

uses
  wclErrors, SysUtils;

{$R *.dfm}
{$R ..\res\Laf.res}

procedure TfmMain.btUnlockClick(Sender: TObject);
var
  Laf: string;
  Res: Integer;
begin
  if cbLaf.ItemIndex = -1 then
    lbLog.Items.Add('No LAF found')

  else begin
    Laf := cbLaf.Text;
    Res := FLaf.Unlock(Laf);
    if Res <> WCL_E_SUCCESS then
      lbLog.Items.Add('Unlock ' + Laf + ' failed: 0x' + IntToHex(Res, 8))
    else
      lbLog.Items.Add('LAF ' + Laf + ' unlocked');
  end;
end;

procedure TfmMain.FormCreate(Sender: TObject);
var
  Res: Integer;
  Pfn: string;
  AppName: string;
  Publisher: string;
  Laf: TStringList;
  i: Integer;
begin
  FLaf := TwclLafManager.Create;

  Res := FLaf.Open;
  if Res <> WCL_E_SUCCESS then
    lbLog.Items.Add('Open LAF Manager failed: 0x' + IntToHex(Res, 8))

  else begin
    lbLog.Items.Add('LAF Manager opened');
    Res := FLaf.GetIdentity(Pfn, AppName, Publisher);
    if Res <> WCL_E_SUCCESS then
      lbLog.Items.Add('Get identity failed: 0x' + IntToHex(Res, 8))

    else begin
      lbLog.Items.Add('PFN: ' + Pfn);
      lbLog.Items.Add('AppName: ' + AppName);
      lbLog.Items.Add('Publisher: ' + Publisher);

      Laf := TStringList.Create;

      Res := FLaf.Enum(Laf);
      if Res <> WCL_E_SUCCESS then
        lbLog.Items.Add('Enum LAF failed: 0x' + IntToHex(Res, 8))

      else begin
        if Laf.Count > 0 then begin
          for i := 0 to Laf.Count - 1 do
            cbLaf.Items.Add(Laf[i]);

          cbLaf.ItemIndex := 0;
        end;
      end;

      Laf.Free;
    end;
  end;
end;

procedure TfmMain.FormDestroy(Sender: TObject);
begin
  FLaf.Free;
end;

end.
