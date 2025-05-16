object fmMain: TfmMain
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'Limited Access Feature Manager Sample Application'
  ClientHeight = 410
  ClientWidth = 518
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object laAvailableLaf: TLabel
    Left = 8
    Top = 16
    Width = 68
    Height = 13
    Caption = 'Available LAF:'
  end
  object cbLaf: TComboBox
    Left = 82
    Top = 13
    Width = 343
    Height = 21
    Style = csDropDownList
    TabOrder = 0
  end
  object btUnlock: TButton
    Left = 431
    Top = 11
    Width = 75
    Height = 25
    Caption = 'Unlock'
    TabOrder = 1
    OnClick = btUnlockClick
  end
  object lbLog: TListBox
    Left = 8
    Top = 42
    Width = 498
    Height = 360
    ItemHeight = 13
    TabOrder = 2
  end
end
