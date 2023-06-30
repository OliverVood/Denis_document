<?php

	namespace Base\DB\MySQLi;

	class FieldID extends Field {
		protected int $size = 10;

		public function __construct(string $name, Table $table, string $description) {
			parent::__construct('id', $name, $table, $description);

			$this->_type = ['int unsigned', "int({$this->size}) unsigned"];
			$this->_null = 'NO';
			$this->_key = 'PRI';
			$this->_default = null;
			$this->_extra = ['auto_increment'];
		}

		private function GetFormat(): string { return "`{$this->name}` int unsigned NOT NULL AUTO_INCREMENT"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }//ALTER TABLE test.users DROP PRIMARY KEY, ADD PRIMARY KEY(USERNAME);

	}