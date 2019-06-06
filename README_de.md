# Neuland

[english](README.md) Deutsch

Ein Karteikarten abfrage System

erlaubt dir Karteikarten zu managen und dich selber mit ihnen abzufragen

## Abhängigkeiten

- mindestens gcc 7 (gcc 9 für die Kompilation für Windows[1])
- jsoncpp
- ncurses
- qt5 & qmake-qt5 (optional)

## Zusammenstellung

### Linux

- Installieren sie alle Abhängigkeiten
- Führe `make` aus
- Führe den Target `qt` aus um mit Qt5 zu kompilieren

### Systemübergreifende Zusammenstellung für Windows

- Klone die M cross environment (MXE)
- Stelle sicher sie includieren die gcc 9 patches
- Kompiliere qt5, ncurses und jsoncpp mit `make qt5 ncurses jsoncpp`
- Führe `make CROSS=i686-w64-mingw32.static-` aus
- Führe den Target `qt` aus um mit Qt5 zu kompilieren

### Windows

 Die Zusammenstellung auf Windows ist derzeit nicht unterstützt



 [1] gcc 9 enthält die Patches damit std::filesystem auf WIndows funktioniert
