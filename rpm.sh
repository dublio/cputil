#!/bin/bash

VERSION=1.0
FILES="cputil.c cputil.1 cputil.spec Makefile LICENSE README.md"

DIR=cputil-$VERSION
TAR=$DIR.tar.gz

rm -rf $DIR
mkdir $DIR

cp cputil.c $DIR
cp cputil.1 $DIR
cp cputil.spec $DIR
cp Makefile $DIR
cp LICENSE $DIR
cp README.md $DIR
cp rpm.sh $DIR

tar -zcvf $TAR $DIR

rm -rf $DIR

TMP=`mktemp -d`
RPMBUILD=$TMP/rpmbuild

mkdir -p $RPMBUILD/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
\cp -f $TAR $RPMBUILD/SOURCES

rpmbuild -ba -D "_topdir $RPMBUILD" cputil.spec

\cp -fr $RPMBUILD/SRPMS/*.rpm .
\cp -fr $RPMBUILD/RPMS/*/*.rpm .

rm -rf $TMP
