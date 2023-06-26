<?php

	namespace Base\DB\MySQLi;

	class FieldInt24 extends Field {
		public function __construct(string $name, Table $table) {
			parent::__construct('int124', $name, $table);

			$this->_type = 'mediumint';
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = '0';
			$this->_extra = '';
		}

		private function GetFormat(): string { return "`{$this->name}` mediumint NOT NULL DEFAULT '0'"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}