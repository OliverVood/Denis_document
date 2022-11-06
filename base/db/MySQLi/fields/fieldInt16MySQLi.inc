<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt16MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('int16', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` smallint NOT NULL DEFAULT '0'"; }

	}