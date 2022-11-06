<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt8MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('uint8', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` tinyint unsigned NOT NULL DEFAULT '0'"; }

	}