

echo -e "           \nADDRESS BOOK\n"
read -p  "Enter Filename : " fname

touch $fname
touch temp
echo -e "\nid\tname\tmobile_no\tlocation\n" >> $fname
ch=0
n=0
create()
{
		echo -e "\n"
		read -p "Enter no.of records to be inserted : " n

		for((i=0;i<$n;i++))
		do
			echo -e "\n"
			read -p "Enter id : " id
			read -p "Enter name : " name
 			read -p "Enter mobile number : " mno
			read -p "Enter location : " loc
			
			echo -e "$id\t$name\t$mno\t$loc" >> $fname
		done
		
}

view()
{
	cat  $fname
}
insert()
{	
	n=n+1
	echo -e "\n"
	read -p "Enter id : " id
	read -p "Enter name : " name
	read -p "Enter mobile number : " mno
	read -p "Enter location : " loc
	echo -e "$id\t$name\t$mno\t$loc " >> $fname
}
delete()
{
	echo -e "\n"
	read -p "Enter Student ID to delete : " id
	
	if grep -w $id $fname
	then
		grep -wv $id $fname >>temp
		rm $fname
		mv temp $fname	
	else
		echo "record not found"
		fi		
}
modify()
{
	echo -e "\n"
	read -p "Enter Student ID to modify : " id
	
	if grep -w $id $fname
	then
		echo -e "\n"
		read -p "Enter id : " new_id
		read -p "Enter name : " new_name
		read -p "Enter mobile number : " new_mno
		read -p "Enter location : " new_loc
		sed "/^$id/c$new_id\t$new_name\t$new_mno\t$new_loc" $fname > temp
		mv temp $fname
					
	else
		echo "Record Not Found"
	fi
}
search()
{
	echo -e "\n"
	read -p "Enter Student id to search : " id
	if grep -w $id $fname
	then
		echo -e "\nRecord found"
	else
		echo -e "\nrecord not found"
	fi	
}
while [ $ch -lt 7 ]
do
	
	echo -e "\n1) Create Address Book"
	echo -e "2) View Address Book"
	echo -e "3) Insert a Record"
	echo -e "4) Delete a Record"
	echo -e "5) Modify a Record"
	echo -e "6) Search a Record"
	echo -e "7) Exit\n"
	read -p "Enter Your choice : " ch
	
	case $ch in 

	1)
		create
		;;
		
 	2)
	        view
	        ;;        


	3) 
		insert
		;;

	4)
		delete
		;;
	5)
		modify
		;;

	6)
		search
		;;

	*)


	esac

done







