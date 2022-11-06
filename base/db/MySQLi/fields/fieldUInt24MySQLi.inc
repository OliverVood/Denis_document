<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt24MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('uint124', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` mediumint unsigned NOT NULL DEFAULT '0'"; }

	}