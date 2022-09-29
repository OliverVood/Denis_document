<?php

	namespace Base\DB;

	abstract class FieldMySQLi extends Field {
		/** @var TableMySQLi $table */

		abstract public function Check(?array $old);
		abstract public function Make();

		protected function DefinitionType(?array $fieldDataDB): ?array {
			$out = ['type' => null, 'string' => ''];
			if ($fieldDataDB['Key'] === "PRI") return ['type' => 'id', 'str' => static::DataToFormatCreate($fieldDataDB)];
//			else ()
//	SHOW COLUMNS FROM `test` FROM `documents`;
//	id	bigint unsigned	NO	PRI NULL auto_increment
//	name	varchar(50)	NO NULL
//	aaa	bigint	YES NULL
//	bbb	bigint	YES NULL
//	asd	varchar(10)	NO NULL
//	dsa	varchar(10)	YES NULL
//	ddd	varchar(10)	YES

			return $out;
		}

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