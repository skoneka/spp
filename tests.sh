echo utworzenie bazy danych
spp --build /tmp/db
echo utworzenie pliku konfiguracyjnego ustawiającego domyślną bazę danych
echo '--data /tmp/db' > ~/.spprc

echo utworzenie przedmiotów i prowadzących
for s in `seq 1 4`;
do
spp --add --type topic --name "przedmiot $s"  --hours 30;
spp --add --type lecturer --name "prowadzący $s" --degree "mgr inż." \
	--room "`expr 500 + $s`";
done

echo edycja prowadzących
spp --edit --type lecturer --id 1 --topic 1,2
spp --edit --type lecturer --id 2 --topic 3,4
spp --edit --type lecturer --id 3 --topic 1
spp --edit --type lecturer --id 4 --topic 3

echo edycja przedmiotów
spp --edit --type topic --id 1 --date "czwartek 10:00" --topic-type egz
spp --edit --type topic --id 2 --date "środa 12:15" --topic-type zal --hours 15
spp --edit --type topic --id 3 --date "poniedziałek 8:15" --topic-type egz
spp --edit --type topic --id 4 --date "wtorek 8:15" --topic-type zal --hours 20

echo wypisanie przedmiotów
spp --cat --type topic

echo utworzenie studentów
for s in `seq 1 30`;
do
spp --add --type student --name "student $s" --index "`expr 300000 + $s`";
done

echo usuwanie studentów
spp --rm --type student --id 6
spp --rm --type student --id 16
spp --rm --type student --id 26

echo edycja studentów
spp --edit --type student --id 1 --name "Jan Kowalski" --topic 1,3,4
spp --edit --type student --id 10 --name "Ola Kowal" --topic 1
spp --edit --type student --id 30 --name "Michał Kowalczuk" --topic 1,2,3,4


spp --cat --type student

echo wypisanie rekordu studenta o id 10
spp --cat --type student --id 10

echo wypisanie powiązań dla studenta
spp --show-links --type student --id 10

echo wypisanie powiązań dla prowadzącego
spp --show-links --type student --id 1

echo wypisanie studentów i prowadzących powiązanych z przedmiotem
spp --show-links --type topic --id 3

echo wypisanie przedmiotów studenta
spp --show-links --type student  --id 10

echo wypisanie przedmiotów prowadzącego
spp --show-links --type lecturer  --id 1

