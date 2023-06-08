<?php

	namespace Base\Editor;

	use Base\DB\Table;

	abstract class Basic {
		protected string $name;
		protected Table $table;

		protected function __construct(string $name, Table $table) {
			$this->name = $name;
			$this->table = $table;
		}

	}