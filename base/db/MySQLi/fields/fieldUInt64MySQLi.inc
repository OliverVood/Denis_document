<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt64MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('uint64', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` bigint unsigned NOT NULL DEFAULT '0'"; }

	}