<?php

	namespace Base\DB\MySQLi;

	class FieldDouble extends Field {
		public function __construct(string $name, Table $table) {
			parent::__construct('double', $name, $table);

			$this->_type = 'double';
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = '0';
			$this->_extra = '';
		}

		private function GetFormat(): string { return "`{$this->name}` double NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}