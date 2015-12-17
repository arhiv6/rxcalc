#define AppName     "RxCalc"
#define AppVersion  "{VERSION}"
#define InputDir    "{INPUTDIR}"
#define OutputDir   "."
[Setup]
AppName={#AppName}
AppVersion={#AppVersion}
AppPublisher="Verkhovin Vyacheslav"
AppPublisherURL="http://sourceforge.net/projects/rxcalc"
AppSupportURL="http://sourceforge.net/projects/rxcalc"
AppUpdatesURL="http://sourceforge.net/projects/rxcalc"
DefaultDirName={pf}\{#AppName}
DefaultGroupName={#AppName}
AllowNoIcons=yes
LicenseFile="{#InputDir}\LICENSE"
OutputDir={#OutputDir}
OutputBaseFilename="{#AppName}-{#AppVersion}_installer"
SetupIconFile="{#InputDir}\windows\installer.ico"
Compression=lzma
SolidCompression=yes   
DirExistsWarning=yes 
ChangesAssociations=true
ChangesEnvironment=true
[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
Name: "catalan"; MessagesFile: "compiler:Languages\Catalan.isl"
Name: "corsican"; MessagesFile: "compiler:Languages\Corsican.isl"
Name: "czech"; MessagesFile: "compiler:Languages\Czech.isl"
Name: "danish"; MessagesFile: "compiler:Languages\Danish.isl"
Name: "dutch"; MessagesFile: "compiler:Languages\Dutch.isl"
Name: "finnish"; MessagesFile: "compiler:Languages\Finnish.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"
Name: "greek"; MessagesFile: "compiler:Languages\Greek.isl"
Name: "hebrew"; MessagesFile: "compiler:Languages\Hebrew.isl"
Name: "hungarian"; MessagesFile: "compiler:Languages\Hungarian.isl"
Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"
Name: "norwegian"; MessagesFile: "compiler:Languages\Norwegian.isl"
Name: "polish"; MessagesFile: "compiler:Languages\Polish.isl"
Name: "portuguese"; MessagesFile: "compiler:Languages\Portuguese.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "serbiancyrillic"; MessagesFile: "compiler:Languages\SerbianCyrillic.isl"
Name: "serbianlatin"; MessagesFile: "compiler:Languages\SerbianLatin.isl"
Name: "slovenian"; MessagesFile: "compiler:Languages\Slovenian.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"
Name: "ukrainian"; MessagesFile: "compiler:Languages\Ukrainian.isl"
[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
[Files]
Source: "{#OutputDir}\release\*"; DestDir: "{app}"; Flags: replacesameversion recursesubdirs createallsubdirs
Source: "{#InputDir}\LICENSE"; DestDir: "{app}"; Flags: replacesameversion
;Source: "{#InputDir}\docs\*"; DestDir: "{app}\docs"; Flags: replacesameversion
;Source: "{#InputDir}\translations\*.qm"; DestDir: "{app}\translations"; Flags: replacesameversion
[Icons]
Name: "{group}\RxCalc"; Filename: "{app}\rxcalc.exe"
Name: "{group}\{cm:ProgramOnTheWeb,RxCalc}"; Filename: "http://sourceforge.net/projects/rxcalc"
Name: "{group}\{cm:UninstallProgram,RxCalc}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\RxCalc"; Filename: "{app}\rxcalc.exe"; Tasks: desktopicon
[Run]
Filename: "{app}\rxcalc.exe"; Description: "{cm:LaunchProgram,RxCalc}"; Flags: nowait postinstall skipifsilent unchecked
[Registry]
Root: HKCR; SubKey: RxCalc_Project;                     ValueType: string; ValueData: "RxCalc Project";               Flags: uninsdeletekey
Root: HKCR; SubKey: RxCalc_Project\Shell\Open\Command;  ValueType: string; ValueData: """{app}\rxcalc.exe"" ""%1""";  Flags: uninsdeletevalue
Root: HKCR; Subkey: RxCalc_Project\DefaultIcon;         ValueType: string; ValueData: {app}\rxcalc.exe;               Flags: uninsdeletevalue
Root: HKCR; SubKey: .rxcp;                              ValueType: string; ValueData: RxCalc_Project;                 Flags: uninsdeletekey
