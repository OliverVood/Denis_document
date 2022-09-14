<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt24 extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('int124', $name);
		}

	}