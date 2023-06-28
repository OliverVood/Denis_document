<?php

	namespace Base\DB\MySQLi;

	class FieldEnum extends Field {
		private array $enum;

		public function __construct(string $name, array $enum, Table $table) {
			parent::__construct('enum', $name, $table);

			$this->enum = $enum;

			$this->_type = ["enum('" . implode("','", $this->enum) . "')"];
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = null;
			$this->_extra = [''];
		}

		private function GetFormat(): string { return "`{$this->name}` enum('" . implode("','", $this->enum) . "') NOT NULL"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}