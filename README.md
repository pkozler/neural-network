# Rozpoznávání číslic neuronovou sítí
Tento program byl vytvořen jako semestrální práce z předmětu Programování v jazyce C.

**Obsah adresáře projektu**

* `src` - zdrojové .JAVA a .FXML soubory programu
* `data` - textové .CSV soubory obsahující základní předdefinovaná data programu
* `javadoc` - vygenerované .HTML soubory programátorské dokumentace
* `training_set` - textové soubory pro trénování klasifikátorů
* `test_set` - textové soubory pro testování klasifikátorů
* `classification_models` - adresář pro ukládání vytvořených klasifikačních modelů (soubory .MODEL)
* `UML.png` - UML diagram tříd
* `Documentation.pdf` - podrobná uživatelská dokumentace

**Příklad použití aplikace**

* Nejprve je nutné z množiny trénovacích dat vytvořit klasifikační model např. následujícím příkazem:
`java -jar DocumentClassification.jar training_set test_set -s -b classification_models/classification`
* Tento klasifikační model poté lze použít nad množinou testovacích dat v GUI, které se zobrazí při spuštění aplikace příkazem:
`java -jar DocumentClassification.jar classification_models/classification`

Detailní popis implementace a návod k použití je k dispozici v přiložené dokumentaci v souboru `Documentation.pdf`.