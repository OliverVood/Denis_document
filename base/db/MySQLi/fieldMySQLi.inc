<?php

	namespace Base\DB;

	abstract class FieldMySQLi extends Field {
		/** @var TableMySQLi $table */

		public function Check(?array $data_field_db) {
			echo "Проверка поля <b>`{$this->name}`</b><br>";
			$instance_field = null;
			if ($data_field_db['Key'] === 'PRI') $str_db = FieldIDMySQLi::DataToCreationFormat($data_field_db);
			else if ($data_field_db['Type'] === 'tinyint(1)') $str_db = FieldBoolMySQLi::DataToCreationFormat($data_field_db);
			$str_st = $this->CreationFormat();

			echo $str_db, '<br>';
			echo $str_st, '<br>';
//			if (($str_st !== $str_db) || ($old['Key'] !== "PRI")) echo "Edit field <b>`{$this->name}`</b>: {$str_db}<br>";
			//$a = 'tinyint(1)';
//			$matches = null;
//			preg_match('/(tinyint)\(([0-9])/', $a, $matches);
//			Debug($matches);

//			else if () {
//				$matches = null;
//				preg_match('/^tinyint\(d+\)$/', $fieldDataDB['Type'], $matches);
//			}
//			return $out;
//		}
		}

		public function Make() { echo "Make field $this->type<br>"; }

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