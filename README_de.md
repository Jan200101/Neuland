# Neuland

Ein Karteikarten abfrage System

erlaubt dir Karteikarten zu managen und dich selber mit ihnen abzufragen

## Abhängigkeiten
 - jsoncpp
 - ncurses
 - qt5 & qmake-qt5 (optional)

## Zusammenstellung

### Linux:
 - Installieren sie alle Abhängigkeiten
 - Führe `make` aus
 - Führe den Target `cli` aus um ohne Qt5 zu kompilieren

### Systemübergreifende Zusammenstellung für Windows
 - Klone die M cross environment (MXE)
 - Kompiliere qt5 und jsoncpp mit `make qt5 jsoncpp`
 - Führe `make CROSS=i686-w64-mingw32.static-` aus
 - Führe den Target `cli` aus um ohne Qt5 zu kompilieren
