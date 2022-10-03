<?php

	namespace Base\DB;

	use Base\DB;

	class FieldTextMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('text', $name, $table);
		}

		protected function CreationFormat(): string { return "`{$this->name}` text NOT NULL"; }

	}