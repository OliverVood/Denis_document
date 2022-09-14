<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt64 extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('int64', $name);
		}

	}