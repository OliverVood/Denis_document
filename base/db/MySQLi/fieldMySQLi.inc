<?php

	namespace Base\DB;

	abstract class FieldMySQLi extends Field {
		/** @var TableMySQLi $table */

		public function Check(?array $data_field_db) : array {
			echo "Проверка поля <b>`{$this->name}`</b><br>";
			$instance_field = null;
			$hash = MD5($data_field_db['DATA_TYPE'] . $data_field_db['COLUMN_TYPE'] . $data_field_db['COLUMN_KEY']);
			$str_db = match ($hash) {
				'c548aac1c21add2c654f222d56e428de' => FieldIDMySQLi::DataToCreationFormat($data_field_db),
				'7cb34ba87823c41bae8c6f04386f682a' => FieldBoolMySQLi::DataToCreationFormat($data_field_db),
				'37d34f7e54e069aba633de62d7738db8' => FieldInt8MySQLi::DataToCreationFormat($data_field_db),
				'c31fd77da49ba5026b3ca9392aeadf94' => FieldInt16MySQLi::DataToCreationFormat($data_field_db),
				'9ed5b32fa483e566850690e62fa561e5' => FieldInt24MySQLi::DataToCreationFormat($data_field_db),
				'61569f2965b7a369eb10b6d75d410d11' => FieldInt32MySQLi::DataToCreationFormat($data_field_db),
				'd7a16cd6f2ddaffe15cb4dc48ec1b97b' => FieldInt64MySQLi::DataToCreationFormat($data_field_db),
				'65093b3353d37f4e9bbdff9660e03d62' => FieldUInt8MySQLi::DataToCreationFormat($data_field_db),
				'f3c9c1029accc228b029cbd1b93c30bf' => FieldUInt16MySQLi::DataToCreationFormat($data_field_db),
				'672f130dde20de0cac1787ad1ff06d6e' => FieldUInt24MySQLi::DataToCreationFormat($data_field_db),
				'8d16fd19bf0e8533d5ca061360fc93dd' => FieldUInt32MySQLi::DataToCreationFormat($data_field_db),
				'084848850747668359cbece882a39586' => FieldUInt64MySQLi::DataToCreationFormat($data_field_db),
				'6a1bb6ed41f44b60e7bd83b0e9945aa7' => FieldFloatMySQLi::DataToCreationFormat($data_field_db),
				'45c855d65dd0e2b57b08024500ff9159' => FieldDoubleMySQLi::DataToCreationFormat($data_field_db),
				'71e24db6312e99e75bdc49e89d65948e' => FieldTimestampMySQLi::DataToCreationFormat($data_field_db),
				'f575f17e6be3f269b86b041a60560dbf' => FieldTextMySQLi::DataToCreationFormat($data_field_db),
				default => match ($data_field_db['DATA_TYPE']) {
					'varchar' => FieldStringMySQLi::DataToCreationFormat($data_field_db),
					'set' => FieldSetMySQLi::DataToCreationFormat($data_field_db),
					'enum' => FieldEnumMySQLi::DataToCreationFormat($data_field_db),
					default => null
				}
			};
			$str_st = $this->CreationFormat();

//			echo $str_db, '<br>';
//			echo $str_st, '<br>';
			if ($str_db !== $str_st) return ['state' => -1, 'name' => $this->name, 'details' => $str_st];
			if (is_null($str_db)) return ['state' => -2, 'name' => $this->name];

			return ['state' => 1];
		}

		public function Make() {
			echo "Make field $this->type<br>";
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

		static protected function DataToCreationFormat($data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';
			$pieces['default'] = "DEFAULT '{$data['COLUMN_DEFAULT']}'";

			return implode(' ', $pieces);
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