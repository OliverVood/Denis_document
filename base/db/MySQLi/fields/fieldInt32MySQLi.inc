<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt32MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('int32', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` int NOT NULL DEFAULT '0'"; }

	}