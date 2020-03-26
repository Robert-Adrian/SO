
#!/bin/bash

while true
do
	clear
	echo "----------------------------------MENIU--------------------------"
	echo "1. Iesire"
	echo "2. Afiseaza informatii masina (numele serverului, tipul masinii-procesorului, tipul sistemului) si calea curenta"
	echo "3. Afiseaza data in format UTC"
	echo "4. Afisarea primelor 2 shell-urilor instalate in sistem"
	echo "5. Afisarea pentru toti utilizatorii din sistem a numelui de login si a directorului de home"
	echo "6. Afisarea ultimelor linii incepand cu linia 9 din fisierul /etc/protocols"
	echo "7. Afisarea tipului de procesor si frecventa de rulare"
	echo "8. Afisarea subdirectoarelor din directorul /proc"
	echo "9. Afisarea si cautare in log-uri:"
	echo "-----------------------------------------------------------------"
	echo "Alege o optiune: "
	read optiune

	if [ $optiune -eq 1 ]
	then
		exit 0
	elif [ $optiune -eq 2 ]
	then
		clear
		echo "Optiunea 2"
		echo "----------------Informatii masina----------------"
		echo "1. Numele serverului: "$HOSTNAME
		echo "2. Tipul masinii-procesorului: "$HOSTTYPE
		echo "3. Tipul sistemului de operare: "$OSTYPE
		echo "4. Calea curenta: "$PWD
		echo "-------------------------------------------------"
		echo "Press ENTER..."
		read enter
	elif [ $optiune -eq 3 ]
	then
		clear
		data=$(date --utc '+%FT%TZ')
		echo "Optiunea 3"
		echo "----------------Data in format UTC---------------"
		echo $data
		echo "-------------------------------------------------"
		echo "Press ENTER..."
		read enter
	elif [ $optiune -eq 4 ]
	then
		clear
		echo "Optiunea 4"
		echo "--------Afisarea primelor 2 shell-uri instalate in sistem--------"
		awk 'BEGIN{total=0}{if($1 != "#" && total < 2){print $1; total+=1}}' /etc/shells
		echo "-----------------------------------------------------------------"
		echo "Press ENTER..."
		read enter
	elif [ $optiune -eq 5 ]
	then
		clear
		echo "Optiunea 5"
		echo "------Afisarea numelui de login si directorul de home------"
		awk -F":" '{print "User:" $1 ", directorul de home:" $6}' /etc/passwd
		echo "-----------------------------------------------------------"
		echo "Press ENTER..."
		read enter
	elif [ $optiune -eq 6 ]
	then
		clear
		echo "Optiunea 6"
		echo "----- Afisarea ultimelor linii incepand cu linia 9 din fisierul /etc/protocols-----"
		length=$(wc -l < /etc/protocols)
		tail -n$(($length-8)) /etc/protocols
		echo "-------------------------------------------------------"
		echo "Press ENTER..."
		read enter
	elif [ $optiune -eq 7 ]
	then
		clear
		echo "Optiunea 7"
		echo "-----Afisare tip procesor si frecventa de rulare-----"
		grep 'processor\|cpu MHz\|model name' /proc/cpuinfo
		echo "-----------------------------------------------------"
		echo "Press ENTER..."
		read enter
	elif [ $optiune -eq 8 ]
	then
		clear
		echo "Optiunea 8"
		echo "--------Afisarea subdirectoarelor din directorul /proc--------"
			comanda=$(ls /proc | grep -oE '[0-9]+')
			for element in  $comanda
			do
				echo $element
			done
		echo "--------------------------------------------------------------"
		echo "Press ENTER..."
		read enter
	elif [ $optiune -eq 9 ]
	then
		logopt=0
		while [ $logopt -ne 3 ]
		do
			clear
			echo "Optiunea 9"
			echo "------------Afisare si cautare in log-uri--------------"
			echo "1. Se vor afisa fisierele de log arhivate"
			echo "2. Afisarea tuturor fisierelor de log. Cautarea unui text in acestea"
			echo "3. Iesire"
			read logopt
			if [ $logopt -eq 1 ]
			then
				clear
				echo "Optiunea 9 -> 1"
				echo "-----------------------------------"
				comanda=$(ls /var/log | grep 'gz$')
				if [ -z $comanda ]
				then
					echo "Nu exista fisiere arhivate"
				else
					for element in $comanda
					do
						echo $element
					done
				fi
				echo "-----------------------------------"
				echo "Press ENTER..."
				read enter
			elif [ $logopt -eq 2 ]
			then
				clear
				echo "Optiunea 9 -> 2"
				echo "----------------------------------"
				afisare_totala=$(ls /var/log)
				for element in $afisare_totala
				do
					echo $element
				done
				echo "Introdu ori un fisier log, ori o arhiva de mai sus: "
				read nume_fisier
				echo "Text de cautat in fisier: "
				read text
				arhiva=$(ls /var/log | grep "^$nume_fisier")
				if [ -z $arhiva ]
				then 
					echo "Nu exista fisierul " $arhiva
				else
					if [[ $arhiva == *".gz" ]]
					then
						find_text=$(gunzip -c /var/log/$arhiva | grep $text | wc -l)
						
						if [[ $find_text = 0 ]]
						then
							echo $text" nu a fost gasit in arhiva"
						else
							echo "Textul "$text" a fost gasit, se afla in arhiva "$arhiva
						fi
					else
						
						find_text=$(grep $text /var/log/$arhiva | wc -l)
												
						if [[ $find_text = 0 ]]
						then
							echo $text " nu a fost gasit in fisier"
						else
							echo "Textul "$text" a fost gasit in fisierul "$arhiva
						fi
					fi
				fi
				
				echo "----------------------------------"
				echo "Press ENTER..."
				read enter
			fi
		done
			echo "-------------------------------------------------------"
	fi

done

