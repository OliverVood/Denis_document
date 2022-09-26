<?php

	namespace Base\DB;

	abstract class FieldMySQLi extends Field {

		abstract public function Check(?array $old);
		abstract public function Make();

//		InfoFieldToStructure();

	}

	require 'fields/fieldIDMySQLi.inc';
	require 'fields/fieldBoolMySQLi.inc';
	require 'fields/fieldInt8MySQLi.inc';
	require 'fields/fieldInt16MySQLi.inc';
	require 'fields/fieldInt24MySQLi.inc';
	require 'fields/fieldInt32MySQLi.inc';
	require 'fields/fieldInt64MySQLi.inc';
	require 'fields/fieldUInt8MySQLi.inc';
	require 'fields/fieldUInt16MySQLi.inc';
	require 'fields/fieldUInt24MySQLi.inc';
	require 'fields/fieldUInt32MySQLi.inc';
	require 'fields/fieldUInt64MySQLi.inc';
	require 'fields/fieldFloatMySQLi.inc';
	require 'fields/fieldDoubleMySQLi.inc';
	require 'fields/fieldTimestampMySQLi.inc';
	require 'fields/fieldEnumMySQLi.inc';
	require 'fields/fieldSetMySQLi.inc';
	require 'fields/fieldStringMySQLi.inc';
	require 'fields/fieldTextMySQLi.inc';