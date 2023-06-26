<?php

	namespace Base\DB\MySQLi;

	class FieldText extends Field {
		public function __construct(string $name, Table $table) {
			parent::__construct('text', $name, $table);

			$this->_type = 'text';
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = null;
			$this->_extra = '';
		}

		private function GetFormat(): string { return "`{$this->name}` text NOT NULL"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}