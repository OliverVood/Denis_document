<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt16MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('uint16', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` smallint unsigned NOT NULL DEFAULT '0'"; }

	}