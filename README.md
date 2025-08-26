# insERT — zadanie rekrutacyjne

## Kilka słów o zadaniu

Tworząc refaktoryzację, starałem się, aby zachowanie programu było jak najbardziej podobne do pierwotnej wersji; dlatego wszystkie operacje wykonują się w podobny sposób jak w otrzymanym pliku `main.cpp`. Uznałem, że właśnie na tym polega refaktoryzacja. Starałem się również, żeby kod był jak najprostszy, schludny i pisany zgodnie z dobrymi standardami. Stąd obecność `clang-tidy` i `clang-format`, które pomagają zachować spójność plików.

## Testy

Testy napisałem, korzystając z **Catch2** jako frameworka testowego oraz **gMock** do mockowania obiektów. W ten sposób połączyłem dwa podejścia wymienione w poleceniu. Jest to również rozwiązanie, z którego korzystałem w projektach komercyjnych, więc byłem pewny tego wyboru.

## Logi
Format logów wygląda następująco: `[Czas] TypLogu Plik:Linia Funkcja Wiadomość`

Zdecydowałem się na taki format, ponieważ daje on pełny pogląd na sytuację: kiedy dana operacja miała miejsce, skąd pochodzi log i w której linii kodu został wygenerowany — dzięki temu można od razu przejść do odpowiedniego fragmentu źródła. W logu znajduje się również nazwa metody oraz komunikat sformatowany przy użyciu `std::format` z biblioteki standardowej , co zapewnia elastyczność co do liczby i typów przekazywanych parametrów.

Przykład logu:
`[2025-08-26 17:10:50] INFO ...\code\src\Database\Database.cpp:164 (Delete): Database deleted object (Document, 15)`
## Budowanie

Projekt budowałem na **Windowsie** przy użyciu **MSVC** oraz presetu dostarczonego w katalogu głównym.


``` cmake --preset VS-MSVC ```

``` cmake --build --preset build-VS-MSVC-Debug ```

## Komendy

Zdecydowałem się na dodanie tylko jednej komendy, jaką jest `--log-file`, która umożliwia zapisanie logów do pliku. W przyszłości istnieje możliwość rozszerzenia klasy Logger, aby obsługiwała także inne typy wyjść. Uruchomienie programu bez tej opcji skutkuje wypisaniem wszystkich logów na konsolę.

``` insERT.exe --log-file "console.log" ```

Komendę `--backup` postanowiłem pozostawić praktycznie bez zmian — zachowuje dotychczasowe działanie. Wywołuje ona opcję systemową, dokładniej: tworzy kopię zapasową dokumentów z bazy danych.

``` insERT.exe --backup" ``` 
