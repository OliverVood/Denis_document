<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt8MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('int8', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` tinyint NOT NULL DEFAULT '0'"; }

	}