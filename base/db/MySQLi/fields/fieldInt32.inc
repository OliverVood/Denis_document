<?php

	namespace Base\DB\MySQLi;

	class FieldInt32 extends Field {
		protected int $size = 10;

		public function __construct(string $name, Table $table, string $description) {
			parent::__construct('int32', $name, $table, $description);

			$this->_type = ['int', "int({$this->size})"];
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = '0';
			$this->_extra = [''];
		}

		private function GetFormat(): string { return "`{$this->name}` int NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}