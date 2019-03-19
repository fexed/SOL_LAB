if [ -d $1 ]; then
	echo "Directory";
	if [ -r $1 ]; then
		echo " leggibile! Procedo.";
		FILEPATH=$(readlink -f "$1");
		NAME=$(basename "$FILEPATH");
		echo $NAME;
		tar -cvf "$NAME".tar.gz $1;
	else echo " illeggibile, stop.";
	fi
else echo "Non è una directory, stop.";
fi
