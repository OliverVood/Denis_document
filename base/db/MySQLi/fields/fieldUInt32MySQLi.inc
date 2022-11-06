<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt32MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('uint32', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` int unsigned NOT NULL DEFAULT '0'"; }

	}