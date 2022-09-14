<?php

	namespace Base\DB;

	abstract class Field {
		protected string $type;
		protected string $name;

		protected function __construct(string $type, string $name) {
			$this->type = $type;
			$this->name = $name;
		}

		public function GetName() {
			return $this->name;
		}

	}