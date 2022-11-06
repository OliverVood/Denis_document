<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt64MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('int64', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` bigint NOT NULL DEFAULT '0'"; }

	}