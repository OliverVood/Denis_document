<?php

	namespace Base\DB;

	abstract class Query {
		abstract public function get(): string;
	}
