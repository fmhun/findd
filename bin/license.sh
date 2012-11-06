#!/usr/bin/env sh

export IFS=

CR="\r\n"
TEMPLATE=".HEADER$CR$CR.COPYRIGHT$CR$CR.AUTHORS$CR$CR.LICENSE"

HEADER="This file is part of the Findd project from University of Poitiers (FR)."
COPYRIGHT="Copyright (C) `date +%Y`"
AUTHORS=`cat AUTHORS`
LICENSE=`cat LICENSE`

CONDITIONS=$TEMPLATE
CONDITIONS=${CONDITIONS//.HEADER/$HEADER}
CONDITIONS=${CONDITIONS//.COPYRIGHT/$COPYRIGHT}
CONDITIONS=${CONDITIONS//.AUTHORS/$AUTHORS}
CONDITIONS=${CONDITIONS//.LICENSE/$LICENSE}

echo $CONDITIONS