<?php

	namespace Base\DB\MySQLi;

	abstract class Field extends \Base\DB\Field {
		const ACTION_OK			=  1;
		const ACTION_CREATE 	= -1;
		const ACTION_UPDATE		= -2;
		const ACTION_DELETE		= -4;

		protected array $_type;
		protected string $_null;
		protected string $_key;
		protected ?string $_default;
		protected array $_extra;

		/** @var Table $table */

		abstract public function CreationFormat(): string;
		abstract public function UpdatingFormat(): string;

		public function Check(array $data): bool {
			if (
				!in_array($data['Type'], $this->_type) ||
				$data['Null'] !== $this->_null ||
				$data['Key'] !== $this->_key ||
				$data['Default'] !== $this->_default ||
				!in_array($data['Extra'], $this->_extra)
			) return false;

			return true;
		}

		public function Create(): bool {
			$this->table->Query("ALTER TABLE `{$this->table->GetName()}` ADD {$this->CreationFormat()}");

			return true;
		}

		public function Update(): string {
			$this->table->Query("ALTER TABLE `{$this->table->GetName()}` CHANGE `{$this->name}` {$this->UpdatingFormat()}");

			return true;
		}

		public function Structure() : array {
			return ['name' => $this->name, 'type' => $this->type, 'description' => $this->description];
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