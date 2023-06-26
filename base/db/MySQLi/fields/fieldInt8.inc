<?php

	namespace Base\DB\MySQLi;

	class FieldInt8 extends Field {
		public function __construct(string $name, Table $table) {
			parent::__construct('int8', $name, $table);

			$this->_type = 'tinyint';
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = '0';
			$this->_extra = '';
		}

		private function GetFormat(): string { return "`{$this->name}` tinyint NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}