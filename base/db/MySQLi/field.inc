<?php

	namespace Base\DB\MySQLi;

	abstract class Field extends \Base\DB\Field {
		const ACTION_OK			=  1;
		const ACTION_CREATE 	= -1;
		const ACTION_VARIOUS	= -2;
		const ACTION_MISSING 	= -3;
		const ACTION_DELETE		= -4;

		/** @var Table $table */

		abstract public function CreationFormat(): string;
		abstract public function UpdatingFormat(): string;

		public function Check(?array $data_field_db): ?array {
			$hash = MD5($data_field_db['DATA_TYPE'] . $data_field_db['COLUMN_TYPE'] . $data_field_db['COLUMN_KEY']);
			$str_db = match ($hash) {
				'c548aac1c21add2c654f222d56e428de' => FieldID::DataToCreationFormat($data_field_db),
				'7cb34ba87823c41bae8c6f04386f682a' => FieldBool::DataToCreationFormat($data_field_db),
				'37d34f7e54e069aba633de62d7738db8' => FieldInt8::DataToCreationFormat($data_field_db),
				'c31fd77da49ba5026b3ca9392aeadf94' => FieldInt16::DataToCreationFormat($data_field_db),
				'9ed5b32fa483e566850690e62fa561e5' => FieldInt24::DataToCreationFormat($data_field_db),
				'61569f2965b7a369eb10b6d75d410d11' => FieldInt32::DataToCreationFormat($data_field_db),
				'd7a16cd6f2ddaffe15cb4dc48ec1b97b' => FieldInt64::DataToCreationFormat($data_field_db),
				'65093b3353d37f4e9bbdff9660e03d62' => FieldUInt8::DataToCreationFormat($data_field_db),
				'f3c9c1029accc228b029cbd1b93c30bf' => FieldUInt16::DataToCreationFormat($data_field_db),
				'672f130dde20de0cac1787ad1ff06d6e' => FieldUInt24::DataToCreationFormat($data_field_db),
				'8d16fd19bf0e8533d5ca061360fc93dd' => FieldUInt32::DataToCreationFormat($data_field_db),
				'084848850747668359cbece882a39586' => FieldUInt64::DataToCreationFormat($data_field_db),
				'6a1bb6ed41f44b60e7bd83b0e9945aa7' => FieldFloat::DataToCreationFormat($data_field_db),
				'45c855d65dd0e2b57b08024500ff9159' => FieldDouble::DataToCreationFormat($data_field_db),
				'71e24db6312e99e75bdc49e89d65948e' => FieldTimestamp::DataToCreationFormat($data_field_db),
				'f575f17e6be3f269b86b041a60560dbf' => FieldText::DataToCreationFormat($data_field_db),
				default => match ($data_field_db['DATA_TYPE']) {
					'varchar' => FieldString::DataToCreationFormat($data_field_db),
					'set' => FieldSet::DataToCreationFormat($data_field_db),
					'enum' => FieldEnum::DataToCreationFormat($data_field_db),
					default => null
				}
			};
			$str_st = $this->CreationFormat();

			if (!$str_db) return ['name' => $this->name, 'action' => self::ACTION_MISSING, 'details' => "Тип не найден ({$data_field_db['COLUMN_NAME']} {$data_field_db['DATA_TYPE']} {$data_field_db['COLUMN_TYPE']} {$data_field_db['COLUMN_KEY']}) -> {$str_st}"];
			if ($str_db !== $str_st) return ['name' => $this->name, 'action' => self::ACTION_VARIOUS, 'details' => "{$str_db} -> {$str_st}"];

			return ['name' => $this->name, 'action' => self::ACTION_OK, 'details' => ''];
		}

		protected static function DataToCreationFormat(array $data): string {
			$pieces = [];
			$pieces['name'] = "`{$data['COLUMN_NAME']}`";
			$pieces['type'] = $data['COLUMN_TYPE'];
			$pieces['null'] = ($data['IS_NULLABLE'] === 'YES') ? 'NULL' : 'NOT NULL';
			$pieces['default'] = "DEFAULT '{$data['COLUMN_DEFAULT']}'";

			return implode(' ', $pieces);
		}

		public function Create(): bool {
			$this->table->Query("ALTER TABLE `{$this->table->GetName()}` ADD {$this->CreationFormat()}");

			return true;
		}

		public function Update(): string {
			$this->table->Query("ALTER TABLE `{$this->table->GetName()}` CHANGE `{$this->name}` {$this->UpdatingFormat()}");

			return true;
		}

	}

	require DIR_BASE . 'db/MySQLi/fields/fieldID.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldBool.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldInt8.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldInt16.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldInt24.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldInt32.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldInt64.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldUInt8.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldUInt16.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldUInt24.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldUInt32.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldUInt64.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldFloat.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldDouble.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldTimestamp.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldEnum.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldSet.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldString.inc';
	require DIR_BASE . 'db/MySQLi/fields/fieldText.inc';